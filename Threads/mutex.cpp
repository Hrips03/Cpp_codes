#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex gLock;
static int shared_var;

void shared_var_inc()
{
    gLock.lock();
        shared_var++;
    gLock.unlock();
}

int main()
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(&shared_var_inc));
        std::cout << threads[i].get_id() << "\n";
    }

    for (size_t i = 0; i < 10; i++)
    {
        threads[i].join(); 
    }

    std::cout << "Shared_var = "<< shared_var <<std::endl;
    return 0;
}