#include <iostream>
#include <thread>
#include <vector>

void test(int x)
{
    std::cout << "Hello from my thread!\n";
    std::cout << "Argument passed in: " << x << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(&test, 10));
        std::cout << threads[i].get_id() << "\n";
        // myThread.join();
    }

    for (size_t i = 0; i < 10; i++)
    {
        threads[i].join(); 
    }

    std::cout << "Hello from main thread!\n";
    return 0;
}