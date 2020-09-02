#include "itask_control.h"


ITaskControl::ITaskControl(const std::size_t number) : iTasks_(number), statuses_(number, READY)
{

}

ITaskControl::~ITaskControl()
{
    for (auto iTask: iTasks_)
    {
        if (iTask != nullptr)
        {
            delete iTask;
        }
    }
}

std::vector<Status> ITaskControl::statuses()
{
    std::size_t size = iTasks_.size();
    for (std::size_t i = 0; i < size; ++i)
    {
        statuses_[i] = iTasks_[i] == nullptr ? READY : iTasks_[i]->status() == READY ? READY : BUSY;
    }
    return statuses_;
}

void ITaskControl::cancel(const std::size_t index)
{
    iTasks_[index]->cancel();
}



