#ifndef ITASK_H
#define ITASK_H

#include <vector>
#include <thread>
#include <future>

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
    void run(F &function, Mode &mode)
    {
        task_ = std::move(function);
        std::string messageFirst = "Начало вычисления !: ";
        std::string messageSecond = "Конец вычисления: ";
        mode == FACTORIAL_1 ? messageSecond += "! = " : (messageFirst += "!",
                                                         messageSecond +="!! = ");
        Logger::info << messageFirst << std::endl;
        thread_ = std::thread([&]()
        {
            task_.wait_for(std::chrono::seconds(0));
        });
        Logger::info << messageSecond << result_ << std::endl;
    }
    void cancel()
    {
        int k = 0;
    }
    Status status()
    {
        auto status = task_.wait_for(std::chrono::seconds(0));
        if (status == std::future_status::ready)
        {
            result_ = task_.get();
            return READY;
        }
        else
        {
            return BUSY;
        }
    }
private:
    bool isProcess = true;
    int result_ = 0;
    std::future<int> task_;
    std::thread thread_;
};

#endif // ITASK_H
