#ifndef ITASK_CONTROL_H
#define ITASK_CONTROL_H

#include <map>
#include <set>
#include <vector>
#include <queue>
#include <future>

#include "itask.hpp"

class ITaskControl
{
public:
    ITaskControl(std::size_t number);
    ~ITaskControl();
    template <typename F>
    void createTask(F &function, std::size_t &index, Mode &&mode)
    {
        if (iTasks_[index] == nullptr)
        {
            iTasks_[index] = new ITask();
        }
        iTasks_[index]->run(function, mode);
    }
    std::vector<ITask*> &getThreads() { return iTasks_; }
private:
    int number_ = 0;
//    pthread_mutex_t queueMutex;
    std::vector<ITask*> iTasks_;
};

#endif // ITASK_CONTROL_H

