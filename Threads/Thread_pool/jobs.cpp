#include "jobs.hpp"

Job::Job(std::function<void()> f) : task(std::move(f)) {}

void Job::execute() {
    task();
}