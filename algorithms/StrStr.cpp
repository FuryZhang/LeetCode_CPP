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
    // myself solution
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

    // leetcode solution
    int strStr1(string haystack, string needle) {
        for (int i = 0; ; ++i)
        {
            for (int j = 0; ; ++j)
            {
                if (j == needle.length())
                {
                    return i;
                }

                if (i + j == haystack.length())
                {
                    return -1;
                }

                if (needle.at(j) != haystack.at(i + j))
                {
                    break;
                }
            }
        }
    }
};
