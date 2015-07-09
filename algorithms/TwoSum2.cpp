#include <vector>
#include <map>

/************************************************************************************************
* 
* Question:
* Given an array of integers that is already sorted in ascending order, find two numbers such
* that they add up to a specific target number.
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
* O(n2) runtime, O(1) space ¨C Brute force:
* The brute force approach is simple. Loop through each element x and find if there is
* another value that equals to target ¨C x. As finding another value requires looping through
* the rest of array, its runtime complexity is O(n2).
* O(n) runtime, O(n) space ¨C Hash table:
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

        int i = 0;
		int j = nums.size() - 1;
		while(i < j)
		{
			int sum = nums.at(i) + nums.at(j);
			if (sum < target)
			{
				i++;
			}
			else if (sum > target)
			{
				j--;
			}
			else
			{
				result.push_back(i + 1);
                result.push_back(j + 1);
                return result;
			}
		}
        return result;
    }
};
