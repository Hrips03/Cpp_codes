#pragma once
#include <thread>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <memory>
#include "jobs.hpp"

class Worker {
public:
    Worker(std::queue<std::shared_ptr<Job>>& jobQueue,
           std::mutex& queueMutex,
           std::condition_variable& condition,
           std::atomic<bool>& stop);

    void start();
    void join();

private:
    void run();

    std::thread thread;
    std::queue<std::shared_ptr<Job>>& jobQueue;
    std::mutex& queueMutex;
    std::condition_variable& condition;
    std::atomic<bool>& stop;
};