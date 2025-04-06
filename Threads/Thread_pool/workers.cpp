#include "workers.hpp"

Worker::Worker(std::queue<std::shared_ptr<Job>> &jq,
               std::mutex &mtx,
               std::condition_variable &cond,
               std::atomic<bool> &st)
    : jobQueue(jq), queueMutex(mtx), condition(cond), stop(st) {}

void Worker::start()
{
    thread = std::thread(&Worker::run, this);
}

void Worker::join()
{
    if (thread.joinable())
        thread.join();
}

void Worker::run()
{
    while (!stop)
    {
        std::shared_ptr<Job> job;
        std::unique_lock<std::mutex> lock(queueMutex);
        condition.wait(lock, [&]()
                       { return !jobQueue.empty() || stop; });
        if (stop && jobQueue.empty())
            return;
        job = jobQueue.front();
        jobQueue.pop();

        job->execute();
    }
}
