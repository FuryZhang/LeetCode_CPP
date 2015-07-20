#include <iostream>
#include "StrStr.cpp"

int main()
{
    string str1 = "A man, a plan, a canal: Panama";
    string str2 = "plan";
    string str3 = "";
    Solution sol;
    int test1 = sol.strStr(str1, str3); // needle is empty, return 0.
    int test2 = sol.strStr(str3, str1); // haystack is empty, return -1.
    int test3 = sol.strStr(str2, str1); // needle's length is greater than haystack's length, return -1.
    int test4 = sol.strStr(str1, str2); // normal

    return 0;
}