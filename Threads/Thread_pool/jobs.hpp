#pragma once
#include <functional>

class Job {
public:
    explicit Job(std::function<void()> f);
    void execute();

private:
    std::function<void()> task;
};
