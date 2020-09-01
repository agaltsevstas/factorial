#include "itask_control.h"


ITaskControl::ITaskControl(std::size_t number) : iTasks_(number)
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

