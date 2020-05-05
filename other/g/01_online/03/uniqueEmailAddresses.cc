/*

https://leetcode.com/problems/unique-email-addresses/

Every email consists of a local name and a domain name, separated by the @ sign.

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.

Besides lowercase letters, these emails may contain '.'s or '+'s.

If you add periods ('.') between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name.  For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.  (Note that this rule does not apply for domain names.)

If you add a plus ('+') in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule does not apply for domain names.)

It is possible to use both of these rules at the same time.

Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails?



Example 1:

Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails

*/

// Solution 1
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        int n, N;
        unordered_set<string> res;
        char chr;
        string newEmail;

        for(auto email: emails) {
            N = email.size();
            newEmail = "";

            // local
            for(n=0; n<N; n++) {
                chr = email[n];
                if(chr == '+' || chr == '@') {
                    break;
                }
                if(chr == '.') {
                    continue;
                }
                newEmail += chr;
            }

            while(n<N && email[n]!='@') {
                n++;
            }

            // domain
            newEmail += email.substr(n);
            res.insert(newEmail);
        }

        return res.size();
    }
};

// Solution 2
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        bool verifyDomain, verifyLocal;
        set<string> st;
        int i;
        string _email;
        for(auto email: emails) {
            verifyDomain = false;
            verifyLocal = true;
            _email = "";
            for(i=0; i<email.size(); i++) {
                if(verifyDomain) {
                    // verify domain part here
                    _email += email[i];
                }
                if(email[i] == '@') {
                    verifyDomain = true;
                    verifyLocal = false;
                    _email += email[i];
                }
                if(verifyLocal) {
                    // verify local part here
                    if(email[i] == '+') {
                        verifyLocal = false;
                    } else if(email[i] == '.') {
                        continue;
                    } else {
                        _email += email[i];
                    }
                }
            }
            st.insert(_email);
        }
        return st.size();
    }
};
