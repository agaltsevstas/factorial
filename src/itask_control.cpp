#include "itask_control.h"
#include "logger.h"

ITaskControl::ITaskControl(std::size_t number) : iTasks_(number)
{
    for (std::size_t i = 0; i < number; ++i)
    {
        idFreeThreads_.insert(i);
    }
}

void ITaskControl::run()
{

}

Status ITaskControl::status()
{
    while (!queue_.empty())
    {
        auto &task = queue_.front();
        Logger::info << "Начало вычисления: " << number_ << "!" << std::endl;
        int result = task.get();
        Logger::info << "Конец вычисления: " << number_ << "! = " << result << std::endl;
        queue_.pop();
    }
    Status busy = ST_BUSY;
    return busy;
}

template <typename F, typename N>
std::shared_ptr<ITaskControl> ITaskControl::createTask(F function, N number)
{
    if (idFreeThreads_.empty())
    {
        queue_.push(std::async(function, number));
    }
    else
    {
        std::size_t index = *idFreeThreads_.begin();
        ITask *itask = iTasks_[index];
        task = new ITask(function, n);
        iTasks_[index]
        idFreeThreads_.erase(index);
    }
}
