/*

https://leetcode.com/problems/next-permutation/

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

*/

// https://leetcode.com/problems/next-greater-element-iii/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int N=nums.size(), i=N-2, j=N-1;

        if(N<2) {
            return;
        }

        while(i>=0 && nums[i]>=nums[i+1]) {
            i--;
        }

        if(i>=0) {
            while(j>=0 && nums[i]>=nums[j]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }

        reverse(nums.begin()+i+1, nums.end());
    }
};


/*
#define LLI long long int

class Solution {
public:
    int stol(string s) {
        LLI num=0;
        for(char ch: s) {
            num = 10*num + (ch-'0');
        }

        if(num>INT_MAX || num<INT_MIN) {
            return -1;
        } else {
            return (int)num;
        }
    }

    int nextGreaterElement(int n) {
        string s=to_string(n);
        int N=s.size(), i=N-2, j=N-1;
        LLI num;

        while(i>=0 && s[i]>=s[i+1]) {
            i--;
        }

        if(i>=0) {
            while(j>=0 && s[i]>=s[j]) {
                j--;
            }
            swap(s[i], s[j]);
        }

        reverse(s.begin()+i+1, s.end());

        num = stol(s);
        return num<=n ? -1 : stoi(s);
    }
};

*/