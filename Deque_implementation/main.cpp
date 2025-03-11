#include "deque.hpp"
#include <iostream>
#include <deque>

int main()
{
    //Assume block size = 4

    Deque<int> deque;
    //Memory - ???
    deque.print();

    Deque<int> deque2(5); 
    deque2.print();
    // Map – [*Block0, *Block1]
    // Block 0: 0 0 0 0
    // Block 1: 0 0 0 0
    //
    // Map_size = 2
    // front_index = 0
    // back_index = 4
    // size = 5

    Deque<int> deque3(6, 8);
    deque3.print();
    // // Map – [*Block0, *Block1]
    // // Block 0: 8 8 8 8
    // // Block 1: 8 8 0 0
    // // 
    // // Map_size = 2
    // // front_index = 0
    // // back_index = 1
    // // size = 6
    

    deque3.push_back(5);
    deque3.print();
    // // Map – [*Block0, *Block1]
    // // Block 0: 8 8 8 8
    // // Block 1: 8 8 5 0
    // //
    // // Map_size = 2
    // // front_index = 0
    // // back_index = 2
    // // size = 7
    

    deque3.push_back(6);
    deque3.print();
    // // Map – [*Block0, *Block1]
    // // Block 0: 8 8 8 8
    // // Block 1: 8 8 5 6
    // //
    // // Map_size = 2
    // // front_index = 0
    // // back_index = 3
    // // size = 8
  

    deque3.push_back(7);
    deque3.print();
    // // Map – [*Block0, *Block1, *Block2]
    // // Block 0: 8 8 8 8
    // // Block 1: 8 8 5 6
    // // Block 2: 7 0 0 0
    // //
    // // Map_size = 3
    // // front_index = 0
    // // back_index = 0
    // // size = 9
    

    deque3.pop_back();
    deque3.print();
    // // Map – [*Block0, *Block1]
    // // Block 0: 8 8 8 8
    // // Block 1: 8 8 5 6
    // //
    // // Map_size = 2
    // // front_index = 0
    // // back_index = 3
    // // size = 8

    // // for (size_t i = 0; i < deque3.size(); i++)
    // //     std::cout << deque3[i] << " "; 
    // // // 8 8 8 8 8 8 5 6 
    // // std::cout << std::endl;

    deque3.pop_back();
    deque3.print();
    // // Map – [*Block0, *Block1]
    // // Block 0: 8 8 8 8
    // // Block 1: 8 8 5 0
    // //
    // // Map_size = 2
    // // front_index = 0
    // // back_index = 2
    // // size = 7


    deque3.push_front(2);
    deque3.print();
    // Map – [*Block-1, *Block0, *Block1]
    // Block -1: 0 0 0 2
    // Block 0: 8 8 8 8
    // Block 1: 8 8 5 0
    //
    // Map_size = 3
    // front_index = 3
    // back_index = 2
    // size = 8

    // for (size_t i = 0; i < deque3.size(); i++)
    //     std::cout << deque3[i] << " "; 
    // // Expected: 2 8 8 8 8 8 8 5 
    // std::cout << std::endl;

    deque3.pop_front();
    deque3.print();
    // Map – [*Block0, *Block1]
    // Block 0: 8 8 8 8
    // Block 1: 8 8 5 0
    //
    // Map_size = 2
    // front_index = 0
    // back_index = 2
    // size = 7

    for (auto it = deque3.begin(); it != deque3.end(); it++)
        std::cout << *it << " "; 
    std::cout << std::endl;
}