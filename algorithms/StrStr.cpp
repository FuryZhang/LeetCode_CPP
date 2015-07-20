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
