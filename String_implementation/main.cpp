#include "string.hpp"

int main(){
    String str = "Hello"; 
    std::cout << str << std::endl;
    String str2 = str;
    std::cout << str2 << std::endl;
    std::cout << "Counter = " << String::counter << std::endl;
    String str3;
    str3 = str2;
    std::cout << str3 << std::endl;
    std::cout << "Counter = " << String::counter << std::endl;

    str2.push_back('a');
    str2.push_back('b');
    str2.pop_back();
    str2.resize(3);
    std::cout << str2 << std::endl;

    str2 = "World!";
    std::cout << str2 << std::endl;
    std::cout << "Counter = " << String::counter << std::endl;


    String str4;
    str4 = std::move(str);
    std::cout << str4 << std::endl;
    String str5 = std::move(str3);
    std::cout << str5 << std::endl;
}