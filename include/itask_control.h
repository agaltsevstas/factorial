#ifndef ITASK_CONTROL_H
#define ITASK_CONTROL_H

#include <set>
#include <vector>
#include <queue>
#include <future>

#include "itask.hpp"

enum Status
{
    ST_READY = 1,
    ST_BUSY
};

class ITaskControl
{
public:
    ITaskControl(std::size_t number);
    void run();
    Status status();
    template <typename F, typename N>
    std::shared_ptr<ITaskControl> createTask(F function, N number);
private:
    int number_ = 0;
//    pthread_mutex_t queueMutex;
    std::set<size_t> idFreeThreads_;
    template <typename F, typename N>
    std::vector<ITask<F, N>*> iTasks_;
    std::queue<std::future<int()>> queue_;

};

#endif // ITASK_CONTROL_H

