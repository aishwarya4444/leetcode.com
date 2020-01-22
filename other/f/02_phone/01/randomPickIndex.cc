/*

https://leetcode.com/problems/random-pick-index/

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);

*/

class Solution {
private:
    unordered_map<int, queue<int> > freq;
public:
    Solution(vector<int>& nums) {
        int n, N=nums.size();
        for(n=0; n<N; n++) {
            freq[nums[n]].push(n);
        }
    }

    int pick(int target) {
        int index = freq[target].front();

        freq[target].pop();
        freq[target].push(index);

        return index;
    }
};



/*
class Solution {
private:
    unordered_map<int, vector<int> > m;
public:
    Solution(vector<int>& nums) {
        int n=0;
        for(auto num: nums) {
            m[num].push_back(n);
            n++;
        }
    }

    int pick(int target) {
        int N = m[target].size(), i;
        i= rand()%N;
        return m[target][i];
    }
};
*/
