#include "task_scheduler.h"
#include <iostream>

TaskScheduler::TaskScheduler(size_t num_threads) : stop(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back(&TaskScheduler::workerThread, this);
    }
}

TaskScheduler::~TaskScheduler() {
    stop = true;
    condition.notify_all();
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void TaskScheduler::schedule(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}

void TaskScheduler::workerThread() {
    while (!stop) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}
