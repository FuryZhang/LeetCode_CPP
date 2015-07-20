#include <string>
using namespace std;
/**************************************************************************
* 
* Question:
* Given a string, determine if it is a palindrome, considering only 
* alphanumeric characters and ignoring cases.
* 
* For example,
* "A man, a plan, a canal: Panama" is a palindrome.
* "race a car" is not a palindrome.
* 
* Note:
* We define empty string as valid palindrome.
* 
* Solution:
* O(n) runtime, O(1) space:
* The idea is simple, have two pointers - one at the head while the other 
* one at the tail.
* Move them towards each other until they meet while skipping 
* non-alphanumeric characters.
* Consider the case where given string contains only non-alphanumeric 
* characters. This is a valid palindrome because the empty string is 
* also a valid palindrome.
* 
**************************************************************************/

class Solution {
public:
    bool isPalindrome(string s)
    {
        int i = 0;
        int j = s.size() - 1;
        while (i < j)
        {
            while (i < j && !isalnum(s.at(i)))
            {
                i++;
            }
            while (i < j && !isalnum(s.at(j)))
            {
                j--;
            }
            if (tolower(s.at(i)) != tolower(s.at(j)))
            {
                return false;
            }
            i++;
            j--;
        }

        return true;
    }
};
