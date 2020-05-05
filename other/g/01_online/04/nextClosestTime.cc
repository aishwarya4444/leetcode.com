/*

https://leetcode.com/problems/next-closest-time/

Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.

*/

// Solution 1
class Solution {
public:
    string nextClosestTime(string time) {
        vector<int> hrs, mins, nums = {time[0]-'0', time[1]-'0', time[3]-'0', time[4]-'0'};
        map<int, pair<int, int> > m;
        int num, tens, units;
        string hour, minute;

        for(tens=0; tens<4; tens++) {
            for(units=0; units<4; units++) {
                num = 10*nums[tens] + nums[units];
                if(num<24) {
                    hrs.push_back(num);
                }
                if(num<60) {
                    mins.push_back(num);
                }
            }
        }

        for(auto hr: hrs) {
            for(auto min: mins) {
                num = 60*hr + min;
                m[num] = make_pair(hr, min);
            }
        }

        num = (10*nums[0]+nums[1])*60 + (10*nums[2]+nums[3]);
        auto index = m.upper_bound(num);

        if(index == m.end()) {
            index = m.begin();
        }

        hour = to_string((*index).second.first);
        minute = to_string((*index).second.second);

        if(hour.size() == 1) {
            hour = '0'+hour;
        }
        if(minute.size() == 1) {
            minute = '0'+minute;
        }

        return hour + ':' + minute;

    }
};

// Solution 2
class Solution {
public:
    string nextClosestTime(string time) {
        int hr, mi, startTime, endTime;
        vector<int> allowed;
        int diff, prevDiff=24*60, res;
        char digit;
        string ans="";



        for(auto digit: time) {
            if(digit!=':') {
                allowed.push_back(digit-'0');
            }
        }

        startTime = 60*(allowed[0]*10+allowed[1])+(allowed[2]*10+allowed[3]);
        // to handle 00:00
        res = startTime;

        for(auto h1: allowed) {
            for(auto h2: allowed) {
                hr = 10*h1+h2;
                if(hr>23) {
                    continue;
                }

                for(auto m1: allowed) {
                    for(auto m2: allowed) {
                        mi = 10*m1+m2;
                        if(mi>59) {
                            continue;
                        }

                        endTime = 60*hr+mi;

                        diff = (endTime-startTime)%(24*60);
                        // to handle startTime == endTime
                        if(diff==0) {
                            continue;
                        }
                        if(diff<0) {
                            diff += 24*60;
                        }
                        if(diff<prevDiff) {
                            res = endTime;
                            prevDiff = diff;
                        }
                    }
                }
            }
        }

        hr = res/60;
        mi = res%60;

        digit = hr/10+'0';
        ans += digit;

        digit = hr%10+'0';
        ans += digit;

        ans += ':';

        digit = mi/10+'0';
        ans += digit;

        digit = mi%10+'0';
        ans += digit;

        return ans;
    }
};
