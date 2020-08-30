#ifndef ITASK_H
#define ITASK_H

#include <vector>
#include <thread>

template <typename F, typename N>
class ITask
{
public:

    ITask(F function, N number) : thread_(new std::thread)
    {
        function_ = function;
        number_ = number;
    };
    void run()
    {
        thread_([&]()
        {
            result_ = function_(number_);
        });
    }
    void cancel()
    {
        thread_ = nullptr;
    }
private:
    N number_;
    F function_;
    int result_ = 0;
    std::thread *thread_ = nullptr;
};

#endif // ITASK_H
