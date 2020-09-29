#ifndef ITASK_H
#define ITASK_H

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <atomic>

#include "logger.h"

class ITask
{
public:

    ITask() {}
    ~ITask() {}
    template <typename F>
    void run(F &task)
    {
        mutex.lock();
        isDone_ = false;
        isInterrupt_ = false;
        packagedTask_ = std::move(std::get<0>(task));
        number_ = std::get<1>(task);
        mode_ = std::get<2>(task);
        task_ = packagedTask_.get_future();
        std::string messageFirst = "Начало вычисления " + std::to_string(number_) + "!";
        if (mode_ == FACTORIAL_2)
        {
            messageFirst += "!";
        }
        Logger::info << messageFirst << std::endl;
        std::thread([&]()
        {
            Logger::info << "ID потока: " << std::this_thread::get_id() << std::endl;
            std::move(packagedTask_)(number_, std::ref(isInterrupt_));
            isDone_ = true;
        }).detach();
        mutex.unlock();
    }
    void cancel()
    {
        isInterrupt_ = true;
        Logger::info << "Прерывание!" << std::endl;
    }
    bool status()
    {
        if (isDone_)
        {
            if (task_.valid())
            {
                result_ = task_.get();
                std::string messageSecond = "Конец вычисления: " + std::to_string(number_);
                            mode_ == FACTORIAL_1 ? messageSecond += "! = " : messageSecond +="!! = ";
                            Logger::info << messageSecond << result_ << std::endl;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    Mode mode_;
    std::atomic<bool> isDone_;
    bool isInterrupt_;
    int number_ = 0;
    int result_ = 0;
    std::packaged_task<int(int, bool&)> packagedTask_;
    std::future<int> task_;
    std::mutex mutex;
};

#endif // ITASK_H
