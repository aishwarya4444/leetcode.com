/*

https://leetcode.com/problems/task-scheduler/

Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks. Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.



Example:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.


Note:

The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].

*/

class Solution {
public:
  int leastInterval(vector<char>& tasks, int n) {
    int intervalCount = 0;
    // TODO: Write your code here
    int node;
    unordered_map<char, int> m;
    priority_queue<int, vector<int>> maxHeap;
    queue<int> waitList;
    int time;

    // populate map
    for(auto task: tasks) {
      m[task]++;
    }

    // populate heap
    for(auto entry: m) {
      maxHeap.push(entry.second);
    }

    while(maxHeap.size()) {
      for(time=0; time<=n && maxHeap.size(); time++) {
        node = maxHeap.top();
        maxHeap.pop();
        node--;
        if(node) {
          waitList.push(node);
        }
      }

      if(waitList.size()) {
            intervalCount += n+1;
            while(waitList.size()) {
            maxHeap.push(waitList.front());
            waitList.pop();
          }
      } else {
          intervalCount += time;
      }
    }
    return intervalCount;
  }
};
