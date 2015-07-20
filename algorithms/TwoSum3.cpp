#include <map>

/************************************************************************************************
* 
* Question:
* Design and implement a TwoSum class. It should support the following operations: add
* and find.
* add(input) - Add the number input to an internal data structure.
* find(value) - Find if there exists any pair of numbers which sum is equal to the value.
* For example,
* add(1); add(3); add(5); find(4)->true; find(7)->false
* 
* Solution:
* add - O(1) runtime, find - O(n) runtime, O(n) space - Store input in hash table:
* A simpler approach is to store each input into a hash table. To find if a pair sum exists,
* just iterate through the hash table in O(n) runtime. Make sure you are able to handle
* duplicates correctly.
* 
************************************************************************************************/

class TwoSum {
public:
    void add(int input)
    {
        int count = table_.find(input) == table_.end() ? 0 : table_[input];
        table_[input] = count + 1;
    }

    bool find(int value)
    {
        for (auto it = table_.begin(); it != table_.end(); ++it)
        {
            int num1 = it->first;
            int num2 = value - num1;
            if (num1 == num2)
            {
                if (it->second >= 2)
                {
                    return true;
                }
            } 
            else if (table_.find(num2) != table_.end())
            {
                return true;
            }
        }

        return false;
    }

private:
    std::map<int, int> table_;
};
