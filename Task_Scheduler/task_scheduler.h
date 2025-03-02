#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class TaskScheduler {
public:
    TaskScheduler(size_t num_threads);
    ~TaskScheduler();

    void schedule(std::function<void()> task);

private:
    void workerThread();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

#endif 
