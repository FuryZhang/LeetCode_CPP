#include <string>
using namespace std;
/**************************************************************************
*
* Question:
* Given an input string s, reverse the string word by word.
* 
* For example,
* Given s = "the sky is blue",
* return "blue is sky the".
*
* Solution:
* O(n) runtime, O(n) space:
* One simple approach is a two-pass solution: First pass to split the string by spaces into an
* array of words, then second pass to extract the words in reversed order.
* 
* We can do better in one-pass. While iterating the string in reverse order, we keep track of
* a word’s begin and end position. When we are at the beginning of a word, we append it.
**************************************************************************/

class Solution {
public:
    void reverseWords(string &s) {
        string reversed;
        int j = s.length(); // 将j初始化为最后一个单词的后面一个位置

        // 对s从后往前遍历，每找到一个单词就添加到reversed后面
        for (int i = s.length() - 1; i >= 0; --i)
        {
            if (s.at(i) == ' ') {
                // 找到单词结束位置
                j = i;
            }
            else if (i == 0 || s.at(i - 1) == ' ') {
                // 找到单词起始位置
                if (!reversed.empty()) {
                    reversed.append(1, ' ');
                }
                reversed.append(s.substr(i, j - i));    // 此时i为单词的第一个字母，j为单词的后面一个位置（类似迭代器的begin和end）
            }
        }

        s = reversed;
    }
};
