#ifndef ITASK_CONTROL_H
#define ITASK_CONTROL_H

#include <vector>
#include <queue>
#include <future>

#include "itask.hpp"

enum Status
{
    READY = 1,
    BUSY
};

class ITaskControl
{
public:
    ITaskControl(const std::size_t number);
    ~ITaskControl();
    template <typename F>
    void createTask(F &task, const std::size_t &index)
    {
        if (!iTasks_[index])
        {
            iTasks_[index] = std::make_shared<ITask>();
        }
        iTasks_[index]->run(task);
    }
    std::vector<Status> statuses();
    void cancel(const std::size_t index);
private:
    std::vector<std::shared_ptr<ITask>> iTasks_;
    std::vector<Status> statuses_;
};

#endif // ITASK_CONTROL_H

