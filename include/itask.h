#ifndef ITASK_H
#define ITASK_H

#include <vector>
#include <thread>

class ITask
{
public:
    void run();
    virtual void cancel() = 0;
protected:
    std::vector<int> ints;
    std::vector<std::thread> threads_;
};

#endif // ITASK_H
