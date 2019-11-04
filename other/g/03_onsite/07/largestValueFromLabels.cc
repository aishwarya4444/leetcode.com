/*

https://leetcode.com/problems/largest-values-from-labels/

We have a set of items: the i-th item has value values[i] and label labels[i].

Then, we choose a subset S of these items, such that:

|S| <= num_wanted
For every label L, the number of items in S with label L is <= use_limit.
Return the largest possible sum of the subset S.



Example 1:

Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], num_wanted = 3, use_limit = 1
Output: 9
Explanation: The subset chosen is the first, third, and fifth item.
Example 2:

Input: values = [5,4,3,2,1], labels = [1,3,3,3,2], num_wanted = 3, use_limit = 2
Output: 12
Explanation: The subset chosen is the first, second, and third item.
Example 3:

Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], num_wanted = 3, use_limit = 1
Output: 16
Explanation: The subset chosen is the first and fourth item.
Example 4:

Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], num_wanted = 3, use_limit = 2
Output: 24
Explanation: The subset chosen is the first, second, and fourth item.


Note:

1 <= values.length == labels.length <= 20000
0 <= values[i], labels[i] <= 20000
1 <= num_wanted, use_limit <= values.length

*/

class Solution {
private:
    struct sortDes {
        bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
            return p1.first > p2.first;
        }
    };
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        unordered_map<int, int> labelFreq;
        vector<pair<int, int>> vl;
        int N=values.size(), val, lab, ans=0;

        for(int i=0; i<N; i++) {
            vl.push_back(make_pair(values[i], labels[i]));
        }

        sort(vl.begin(), vl.end(), sortDes());

        for(auto node: vl) {
            val = node.first;
            lab = node.second;
            labelFreq[lab]++;
            if(labelFreq[lab] <= use_limit && num_wanted) {
                ans += val;
                num_wanted--;
            }
        }
        return ans;
    }
};
