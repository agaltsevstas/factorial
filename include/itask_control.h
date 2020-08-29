#ifndef ITASK_CONTROL_H
#define ITASK_CONTROL_H

#include "itask.h"

enum Status
{
    ST_READY = 1,
    ST_BUSY
};

class ITaskControl: public ITask
{
public:
    void run();
    Status status();
};

#endif // ITASK_CONTROL_H

