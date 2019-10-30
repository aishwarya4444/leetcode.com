/*

https://leetcode.com/problems/moving-average-from-data-stream/

Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Example:

MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3

*/

class MovingAverage {
private:
    queue<int> q;
    int N;
    long long int sum;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        N = size;
        sum = 0;
    }

    double next(int val) {
        q.push(val);
        sum += val;
        if(q.size() > N) {
            sum -= q.front();
            q.pop();
        }
        return sum*1.0/q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
