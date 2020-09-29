#include "itask_control.h"


ITaskControl::ITaskControl(const std::size_t number) : iTasks_(number), statuses_(number, READY)
{

}

ITaskControl::~ITaskControl() {}

std::vector<Status> ITaskControl::statuses()
{
    std::size_t size = iTasks_.size();
    for (std::size_t i = 0; i < size; ++i)
    {
        statuses_[i] = iTasks_[i] ? iTasks_[i]->status() == READY ? READY : BUSY : READY;
    }
    return statuses_;
}

void ITaskControl::cancel(const std::size_t index)
{
    iTasks_[index]->cancel();
}



