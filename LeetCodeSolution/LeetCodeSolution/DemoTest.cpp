#include <iostream>
#include "TwoSum2.cpp"

int main()
{
    int a[4] = {2, 7, 11, 15};
    std::vector<int> vin(a, a + 4);
    Solution solution;
    std::vector<int> vout = solution.twoSum(vin, 9);
    return 0;
}