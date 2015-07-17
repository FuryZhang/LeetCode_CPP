#include <iostream>
#include "TwoSum3.cpp"

int main()
{
    TwoSum ts3;
    ts3.add(1);
    ts3.add(3);
    ts3.add(5);

    bool test1 = ts3.find(4);
    bool test2 = ts3.find(7);
    
    return 0;
}