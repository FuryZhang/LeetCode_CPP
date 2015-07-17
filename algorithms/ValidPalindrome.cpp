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
* The idea is simple, have two pointers ¨C one at the head while the other 
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
        string temp;
        for (int i = 0; i < s.size(); ++i)
        {
            char a = s.at(i);
            if (a >= 'A' && a <= 'Z')
            {
                temp.append(1, char(a + 'a' - 'A'));
                continue;
            }

            if (a >= 'a' && a<= 'z' || a >= '0' && a <= '9')
            {
                temp.append(1, a);
            }
        }

        int i = 0;
        int j = temp.size() - 1;
        while (i < j)
        {
            if (temp.at(i) != temp.at(j))
            {
                return false;
            }
            i++;
            j--;
        }

        return true;
    }
};
