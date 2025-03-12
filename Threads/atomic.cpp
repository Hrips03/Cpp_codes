#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> shared_var;

void shared_var_inc()
{
    shared_var++;
}

int main()
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(&shared_var_inc));
    }

    for (size_t i = 0; i < 10; i++)
    {
        threads[i].join(); 
    }

    std::cout << "Shared_var = "<< shared_var <<std::endl;
    return 0;
}