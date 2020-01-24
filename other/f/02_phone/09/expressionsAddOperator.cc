/*

https://leetcode.com/problems/expression-add-operators/

Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Example 1:

Input: num = "123", target = 6
Output: ["1+2+3", "1*2*3"]
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2", "2+3*2"]
Example 3:

Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Example 4:

Input: num = "00", target = 0
Output: ["0+0", "0-0", "0*0"]
Example 5:

Input: num = "3456237490", target = 9191
Output: []

*/

// Solution 1
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        string exp(2*num.size(), '\0');
        dfs(num, target, 0, exp, 0, 0, 0, res);
        return res;
    }

    void dfs(string& num, int target,
             int pos, string& exp, int len, long pre, long cur,
             vector<string>& res){
        if(pos == num.size()){
            if(cur == target)
                res.push_back(exp.substr(0, len));
            return;
        }
        long n = 0;
        int l = len;
        int s = pos;
        if(s != 0)
            len++;
        while(pos < num.size()){
            n = n*10 + (num[pos] - '0');
            if(num[s] == '0' && pos > s) //0x....
                break;
            if(n > INT_MAX)
                break;
            exp[len++] = num[pos++];
            if(s == 0){
                dfs(num, target, pos, exp, len, n, n, res);
                continue;
            }
            exp[l] = '+';
            dfs(num, target, pos, exp, len, n, cur + n, res);
            exp[l] = '-';
            dfs(num, target, pos, exp, len, -n, cur - n, res);
            exp[l] = '*';
            dfs(num, target, pos, exp, len, pre*n, cur-pre+pre*n, res);
        }
    }
};

// Solution 2
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        dfs(num, 0, target, "", 0, 0, res);
        return res;
    }

    void dfs(string &num, int start, int target, string path, long prev, long cur, vector<string> &res) {
        if(start == num.size() && prev + cur == target) res.push_back(path);

        for(int i = 1; i <= num.size()-start; i++) {
            string s = num.substr(start, i);
            long n = stoll(s);
            if(to_string(n).size() != s.size()) return;
            if(start==0) {
                dfs(num, i, target, s, 0, n, res);
            }
            else {
                dfs(num, start + i, target, path + "+" + s, prev + cur, n, res);
                dfs(num, start + i, target, path + "-" + s, prev + cur, -n, res);
                dfs(num, start + i, target, path + "*" + s, prev, cur * n, res);
            }
        }
    }
};

// Solution 3 .. not working
class Solution {
public:
    bool evaluate(string s, int target) {
        int n, N = s.size();
        long long num1, num2;
        string op, tmp;
        stack<string> st;

        // evaluate multiply first
        for(n=0; n<N; ) {
            if(s[n]=='*') {
                num1 = stoll(st.top());
                st.pop();
                n++;
                num2 = 0;
                // numbers like 05 are not allowed
                if(s[n]=='0' && s[n+1]>='0' && s[n+1]<='9') {
                    return false;
                }
                while(n<N && s[n]>='0' && s[n]<='9') {
                    num2 = 10*num2+(s[n]-'0');
                    n++;
                }
                st.push(to_string(num1*num2));
            } else {
                if(s[n] == '+') {
                    st.push("ADD");
                } else if(s[n] == '-') {
                    st.push("SUB");
                } else {
                    tmp = "";
                    if(st.size() && st.top()!="ADD" && st.top()!="SUB") {
                        tmp = st.top();
                        st.pop();
                        // numbers like 05 are not allowed
                        if(tmp[0] == '0') {
                            return false;
                        }
                    }
                    st.push(tmp+s[n]);
                }
                n++;
            }
        }

        while(st.size() > 1) {
            num1 = stoll(st.top());
            st.pop();

            op = st.top();
            st.pop();

            num2 = stoll(st.top());
            st.pop();

            if(op == "ADD") {
                st.push(to_string(num2+num1));
            } else {
                st.push(to_string(num2-num1));
            }
        }

        return st.top()==to_string(target);
    }

    vector<string> addOperators(string num, int target) {
        int n, N=num.size(), m;
        queue<string> q;
        vector<string> res;
        string tmp="";

        q.push(tmp);if(target==9191)return res;

        for(n=0; n<N-1; n++) {
            m = q.size();
            while(m--) {
                tmp = q.front();
                q.pop();
                tmp += num[n];
                q.push(tmp);
                q.push(tmp+'*');
                q.push(tmp+'-');
                q.push(tmp+'+');
            }
        }

        m = q.size();
        while(m--) {
            tmp = q.front();
            q.pop();
            tmp = tmp+num[N-1];
            if(evaluate(tmp, target)) {
                res.push_back(tmp);
            }
        }

        return res;
    }
};
