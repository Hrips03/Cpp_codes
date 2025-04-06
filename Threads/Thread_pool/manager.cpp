#include "manager.hpp"

Manager::Manager(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        auto worker = std::make_unique<Worker>(jobQueue, queueMutex, condition, stop);
        worker->start();
        workers.push_back(std::move(worker));
    }
}

Manager::~Manager() {
    stop = true;
    condition.notify_all();
    for (auto& worker : workers) {
        worker->join();
    }
}

void Manager::submit(std::function<void()> func) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        jobQueue.push(std::make_shared<Job>(func));
    }
    condition.notify_one();
}
