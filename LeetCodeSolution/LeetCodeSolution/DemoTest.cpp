#include <iostream>
#include "ReverseWordsInAString.cpp"

int main()
{
    string str1 = "A man, a plan, a canal: Panama";
    string str2 = "plan";
    string str3 = "the sky is blue";
    int a = str3.length() - 1;
    Solution sol;
    sol.reverseWords(str3);

    return 0;
}