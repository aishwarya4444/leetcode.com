/*

https://leetcode.com/problems/minimum-cost-to-hire-k-workers/

There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum wage expectation.
Return the least amount of money needed to form a paid group satisfying the above conditions.



Example 1:

Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.


Note:

1 <= K <= N <= 10000, where N = quality.length = wage.length
1 <= quality[i] <= 10000
1 <= wage[i] <= 10000
Answers within 10^-5 of the correct answer will be considered correct.

*/

/*
https://leetcode.com/problems/minimum-cost-to-hire-k-workers/discuss/370149/c%2B%2B-clean-code-max-heap
*/

class Solution {
public:
    struct compareMin {
        bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
            return p1.first*p2.second > p2.first*p1.second;
            // w1/q1 > w2/q2
        }
    };

    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, compareMin> minHeap;
        priority_queue<int, vector<int>, less<int>> maxHeap;
        int i, N=quality.size(), qual=0;
        double cost=numeric_limits<double>::max();

        for(i=0; i<N; i++) {
            minHeap.push({wage[i], quality[i]});
        }

        while(minHeap.size()) {
            auto minNode = minHeap.top();
            minHeap.pop();
            qual += minNode.second;
            maxHeap.push(minNode.second);
            if(maxHeap.size() > K) {
                qual -= maxHeap.top();
                maxHeap.pop();
            }
            if(maxHeap.size() == K) {
                cost = min(cost, 1.0*minNode.first*qual/minNode.second);
            }
        }

        return cost;
    }
};
