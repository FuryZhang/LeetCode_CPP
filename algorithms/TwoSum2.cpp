#include <vector>

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
* O(n) runtime, O(1) space ¨C Two pointers:
* Let's assume we have two indices pointing to the i th and j th elements, A i and A j
* respectively. The sum of A i and A j could only fall into one of these three possibilities:
* i.  A i + A j > target. Increasing i isn't going to help us, as it makes the sum even
* bigger. Therefore we should decrement j.
* ii.  A i + A j < target. Decreasing j isn't going to help us, as it makes the sum even
* smaller. Therefore we should increment i.
* iii.  A i + A j == target. We have found the answer.
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
