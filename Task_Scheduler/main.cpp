#include "task_scheduler.h"
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;  

void exampleTask(int id) {
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Task " << id << " is running on thread " << std::this_thread::get_id() << "\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Task " << id << " completed\n";
    }
}

int main() {
    TaskScheduler scheduler(4); 

    for (int i = 1; i <= 10; ++i) {
        scheduler.schedule([i] { exampleTask(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5)); 
    return 0;
}
