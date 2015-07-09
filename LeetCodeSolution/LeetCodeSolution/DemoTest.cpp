#include <iostream>
#include "TwoSum.cpp"

int main()
{
    int a[4] = {2, 7, 11, 2};
    std::vector<int> vin(a, a + 4);
    Solution solution;
    std::vector<int> vout = solution.twoSum(vin, 4);
    return 0;
}