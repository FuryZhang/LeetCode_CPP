#include <vector>
#include <map>

/************************************************************************************************
* 
* Question:
* Given an array of integers, find two numbers such that they add up to a specific target number.
* 
* The function twoSum should return indices of the two numbers such that they add up to
* the target, where index1 must be less than index2. Please note that your returned answers
* (both index1 and index2) are not zero-based.
* 
* You may assume that each input would have exactly one solution.
* 
* Input: numbers={2, 7, 11, 15}, target=9
* Output: index1=1, index2=2
* 
* Solution:
* O(n2) runtime, O(1) space - Brute force:
* The brute force approach is simple. Loop through each element x and find if there is
* another value that equals to target - x. As finding another value requires looping through
* the rest of array, its runtime complexity is O(n2).
* O(n) runtime, O(n) space - Hash table:
* We could reduce the runtime complexity of looking up a value to O(1) using a hash map
* that maps a value to its index.
* 
************************************************************************************************/

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> result;
        if (nums.size() < 2)
        {
            return result;
        }

        std::map<int, int> num_index_map;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto it = num_index_map.find(target - nums.at(i));
            if (it != num_index_map.end())
            {
                result.push_back(it->second + 1);
                result.push_back(i + 1);
                return result;
            }
            num_index_map[nums.at(i)] = i;
        }
        return result;
    }
};
