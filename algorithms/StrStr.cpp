#include <string>
using namespace std;
/**************************************************************************
* 
* Question:
* Implement strStr().
* 
* Returns the index of the first occurrence of needle in haystack, 
* or -1 if needle is not part of haystack.
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
    int strStr(string haystack, string needle) {
        const int hssize = haystack.size();
        const int nsize = needle.size();
        const char *hs = haystack.c_str();
        const char *n = needle.c_str();
        for (int i = 0; i < hssize - nsize + 1; ++i)
        {
            if (strncmp(hs + i, n, nsize) == 0)
            {
                return i;
            }
        }
        return -1;
    }
};
