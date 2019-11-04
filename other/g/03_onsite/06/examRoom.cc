/*

https://leetcode.com/problems/exam-room/

In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.

When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.  If there are multiple such seats, they sit in the seat with the lowest number.  (Also, if no one is in the room, then the student sits at seat number 0.)

Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat() returning an int representing what seat the student sat in, and ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.  It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.



Example 1:

Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
Output: [null,0,9,4,2,null,5]
Explanation:
ExamRoom(10) -> null
seat() -> 0, no one is in the room, then the student sits at seat number 0.
seat() -> 9, the student sits at the last seat number 9.
seat() -> 4, the student sits at the last seat number 4.
seat() -> 2, the student sits at the last seat number 2.
leave(4) -> null
seat() -> 5, the student sits at the last seat number 5.
​​​​​​​

Note:

1 <= N <= 10^9
ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
Calls to ExamRoom.leave(p) are guaranteed to have a student currently sitting in seat number p.

*/

class ExamRoom {
private:
    int S;
    set<int> seats;
public:
    ExamRoom(int N) {
        S = N;
    }

    int seat() {
        int seat = 0;

        if(seats.size()) {
            int maxDiff=0, diff, prev = seats.count(0) ? 0 : -*seats.begin();
            for(int curr: seats) {
                diff = (curr-prev)/2;
                if(diff > maxDiff) {
                    seat = (curr+prev)/2;
                    maxDiff = diff;
                }
                prev = curr;
            }
            if(seats.count(S-1) == 0) {
                diff = S-1-prev;
                if(diff>maxDiff) {
                    seat = S-1;
                }
            }
        }

        seats.insert(seat);
        return seat;
    }

    void leave(int p) {
        seats.erase(p);
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */

 /*
 class ExamRoom {
 private:
     int seats, count;
     set<int> filled;
 public:
     ExamRoom(int N) {
         count = 0;
         seats = N;
     }

     int seat() {
         count++;
         if(count == 1) {
             filled.insert(0);
             return 0;
         }

         vector<int> v;
         for(auto fill: filled) {
             v.push_back(fill);
         }

         int n, N=v.size(), seat=0, diff=v[0];

         for(n=0; n<N-1; n++) {
             if(diff < (v[n+1]-v[n])/2) {
                 diff = (v[n+1]-v[n])/2;
                 seat = (v[n+1]+v[n])/2;
             }
         }

         // for (N-1)th seat
         if(diff < seats-1-v[N-1]) {
             diff = seats-1-v[N-1];
             seat = seats-1;
         }

         filled.insert(seat);
         return seat;
     }

     void leave(int p) {
         filled.erase(p);
         count--;
     }

 };
 */
