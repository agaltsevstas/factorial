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
    void createTask(F &task, const std::size_t &index)
    {
        if (iTasks_[index] == nullptr)
        {
            iTasks_[index] = new ITask();
        }
        iTasks_[index]->run(task);
    }
    std::vector<ITask*> *getThreads() { return &iTasks_; }
private:
    std::vector<ITask*> iTasks_;
};

#endif // ITASK_CONTROL_H

