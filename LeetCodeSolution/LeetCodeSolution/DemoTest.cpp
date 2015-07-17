#include <iostream>
#include "ValidPalindrome.cpp"

int main()
{
    string str1 = "A man, a plan, a canal: Panama";
    string str2 = "race a car";
    Solution sol;
    bool test1 = sol.isPalindrome(str1);
    bool test2 = sol.isPalindrome(str2);

    return 0;
}