#ifndef ITASK_CONTROL_H
#define ITASK_CONTROL_H

#include <vector>
#include <queue>
#include <future>

#include "itask.hpp"

class ITaskControl
{
public:
    ITaskControl(const std::size_t number);
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
    std::vector<Status> statuses();
    void cancel(const std::size_t index);
private:
    std::vector<ITask*> iTasks_;
    std::vector<Status> statuses_;
};

#endif // ITASK_CONTROL_H

