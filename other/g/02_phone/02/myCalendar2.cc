/*

https://leetcode.com/problems/my-calendar-ii/

Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.

Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
Explanation:
The first two events can be booked.  The third event can be double booked.
The fourth event (5, 15) can't be booked, because it would result in a triple booking.
The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.


Note:

The number of calls to MyCalendar.book per test case will be at most 1000.
In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

*/

class MyCalendarTwo {
private:
    map<int, int> freq;
public:
    MyCalendarTwo() {

    }

    bool book(int start, int end) {
        int count=0;

        freq[start]++;
        freq[end]--;

        for(auto entry: freq) {
            count += entry.second;
            if(count>=3) {
                freq[start]--;
                freq[end]++;
                if(freq[start] == 0) {
                    freq.erase(start);
                }
                if(freq[end] == 0) {
                    freq.erase(end);
                }
                return false;
            }
        }

        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */



 /*

// Similar question :: My Calendar 1
// double booking should not happen
// solution uses interval tree
// https://leetcode.com/problems/my-calendar-i/discuss/412363/C%2B%2B-Using-Interval-Tree-Easy-to-understand.

class MyCalendar {
private:
    map<int, size_t> freq;
    struct TreeNode {
        int start, end;
        TreeNode *left, *right;
        TreeNode(int s, int e) {
            start = s;
            end = e;
            left = NULL;
            right = NULL;
        }
    };

    TreeNode *root;

public:
    MyCalendar() {
        root = NULL;
    }

    // TLE
    // bool book(int start, int end) {
    //     int i;
    //     for(i=start; i<end; i++) {
    //         if(freq[i]==1) {
    //             return false;
    //         }
    //     }
    //     for(i=start; i<end; i++) {
    //         freq[i]++;
    //     }
    //     return true;
    // }

    bool book(int start, int end) {
        TreeNode *curr=root, *prev=NULL;

        end--;
        if(!curr) {
            root = new TreeNode(start, end);
            return true;
        }

        while(curr) {
            prev = curr;
            if(end<curr->start) curr=curr->left;
            else if(curr->end<start) curr=curr->right;
            else return false;
        }
        if(end<prev->start) {
            prev->left = new TreeNode(start, end);
        } else {
            prev->right = new TreeNode(start, end);
        }
        return true;
    }
};

 */
