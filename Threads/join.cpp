#include <iostream>
#include <thread>

void test(int x)
{
    std::cout << "Hello from my thread!\n";
    std::cout << "Argument passed in: " << x << std::endl;
}

auto lamda = [](int x){
    std::cout << "Hello from my 3rd thread!\n";
    std::cout << "Argument passed in: " << x << std::endl;
};

int main()
{

    std::thread myThread(&test, 10);
    myThread.join();

    std::thread myThread2([](){
        std::cout << "Hello from my 2nd thread!\n";
    });
    myThread2.join();

    std::thread myThread3(lamda, 20);
    myThread3.join();

    std::cout << "Hello from main thread!\n";
    return 0;
}