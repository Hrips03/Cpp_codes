#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include "jobs.hpp"
#include "workers.hpp"

class Manager {
public:
    explicit Manager(size_t numThreads);
    ~Manager();

    void submit(std::function<void()> func);

private:
    std::vector<std::unique_ptr<Worker>> workers;
    std::queue<std::shared_ptr<Job>> jobQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};