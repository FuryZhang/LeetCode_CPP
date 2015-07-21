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
* a word��s begin and end position. When we are at the beginning of a word, we append it.
**************************************************************************/

class Solution {
public:
    void reverseWords(string &s) {
        string reversed;
        int j = s.length(); // ��j��ʼ��Ϊ���һ�����ʵĺ���һ��λ��

        // ��s�Ӻ���ǰ������ÿ�ҵ�һ�����ʾ���ӵ�reversed����
        for (int i = s.length() - 1; i >= 0; --i)
        {
            if (s.at(i) == ' ') {
                // �ҵ����ʽ���λ��
                j = i;
            }
            else if (i == 0 || s.at(i - 1) == ' ') {
                // �ҵ�������ʼλ��
                if (!reversed.empty()) {
                    reversed.append(1, ' ');
                }
                reversed.append(s.substr(i, j - i));    // ��ʱiΪ���ʵĵ�һ����ĸ��jΪ���ʵĺ���һ��λ�ã����Ƶ�������begin��end��
            }
        }

        s = reversed;
    }
};
