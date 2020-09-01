#ifndef ITASK_H
#define ITASK_H

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <atomic>

#include "logger.h"


enum Status
{
    READY = 1,
    BUSY
};

enum Mode
{
    FACTORIAL_1 = 1,
    FACTORIAL_2
};

class ITask
{
public:

    ITask() {}
    ~ITask() {}
    template <typename F>
    void run(F &task)
    {
        done_ = false;
        auto &packagedTask = std::get<0>(task);
        number_ = std::get<1>(task);
        Mode mode = std::get<2>(task);
        task_ = packagedTask.get_future();
        std::string messageFirst = "Начало вычисления " + std::to_string(number_) + "!";
        std::string messageSecond = "Конец вычисления: " + std::to_string(number_);
        mode == FACTORIAL_1 ? messageSecond += "! = " : (messageFirst += "!",
                                                         messageSecond +="!! = ");
        Logger::info << messageFirst << std::endl;
        std::thread([&]()
        {
            packagedTask(number_, std::ref(isProcess_));
            done_ = true;
//            task_.wait_for(std::chrono::seconds(0));
        }).detach();
//        result_ = task_.get();
//        std::thread(std::move(packagedTask), number_, std::ref(isProcess_));
        Logger::info << messageSecond << result_ << std::endl;

    }
    void cancel()
    {
        isProcess_ = false;
        Logger::info << "Прерывание!" << std::endl;
    }
    Status status()
    {
        if (done_)
        {
//            result_ = task_.get();
            return READY;
        }
        else
        {
            return BUSY;
        }
//        auto status = task_.wait_for(std::chrono::seconds(0));
//        if (status == std::future_status::ready)
//        {
////            result_ = task_.get();
//            return READY;
//        }
//        else
//        {
//            return BUSY;
//        }
    }
private:
    std::atomic<bool> done_;
    int number_ = 0;
    bool isProcess_ = true;
    int result_ = 0;
    std::future<int> task_;
};

#endif // ITASK_H
