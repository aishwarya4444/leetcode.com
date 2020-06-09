/*

https://leetcode.com/problems/meeting-rooms-ii/

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2
Example 2:

Input: [[7,10],[2,4]]
Output: 1
NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

*/

// Solution 1
class Solution {
private:
    struct compareAscending {
        bool operator()(vector<int> &v1, vector<int> &v2) {
            if(v1[0]==v2[0]) {
                return v1[0]<v2[0];
            }
            return v1[0]<v2[0];
        }
    };

    struct compareMin {
        bool operator()(int &n1, int &n2) {
            return n1 > n2;
        }
    };

public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        // min heap
        priority_queue<int, vector<int>, compareMin > rooms;
        int minRooms = 0, start, end;

        sort(intervals.begin(), intervals.end(), compareAscending());

        for(auto interval: intervals) {
            start = interval[0];
            end = interval[1];
            if(rooms.size()) {
                while(rooms.size() && start>=rooms.top()) {
                    rooms.pop();
                }
                rooms.push(end);
            } else {
                rooms.push(end);
            }
            minRooms = max(minRooms, (int)rooms.size());
        }

        return minRooms;
    }
};

// Solution 2
class Solution {
private:
    struct compareMin {
        bool operator()(int &n1, int &n2) {
            return n1 > n2;
        }
    };

public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        // min heap
        priority_queue<int, vector<int>, compareMin > rooms;
        int minRooms = 0, start, end;

        sort(intervals.begin(), intervals.end());

        for(auto interval: intervals) {
            start = interval[0];
            end = interval[1];
             while(rooms.size() && start>=rooms.top()) {
                rooms.pop();
            }
            rooms.push(end);
            minRooms = max(minRooms, (int)rooms.size());
        }

        return minRooms;
    }
};

// Solution 3
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> meet;
        int sum = 0, rooms = 0;

        for(auto i: intervals) {
            meet[i[0]]++;
            meet[i[1]]--;
        }

        for(auto m: meet) {
            sum += m.second;
            rooms = max(rooms, sum);
        }

        return rooms;
    }
};