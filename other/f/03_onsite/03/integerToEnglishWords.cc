/*

https://leetcode.com/problems/integer-to-english-words/

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

Example 1:

Input: 123
Output: "One Hundred Twenty Three"
Example 2:

Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Example 3:

Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Example 4:

Input: 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

*/

class Solution {
private:
    vector<string> suffix = {"Hundred ", "Thousand ", "Million ", "Billion "};
    vector<string> units = {"Zero ", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine "};
    vector<string> tens = {"", "Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety "};
    vector<string> tensSpecial = {"Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};
public:

    string threeDigitsToWord(int num, int suffixCount) {
        string res = "";
        int unit, ten, hundred;

        if(num==0) {
            return res;
        }

        unit = num%10;
        ten = (num%100)/10;
        hundred = num/100;

        if(hundred > 0) {
            res = units[hundred] + suffix[0];
        }

        if(ten == 0) {
            res += unit ? units[unit] : "";
        } else if(ten == 1) {
            res += tensSpecial[unit];
        } else {
            res += tens[ten];
            res += unit ? units[unit] : "";
        }

        if(suffixCount) {
            res += suffix[suffixCount];
        }

        return res;
    }

    string numberToWords(int num) {
        string res;
        int count=0;

        if(num==0) {
            res = units[num];
            res[res.size()-1] = '\0';
            return res;
        }

        while(num) {
            res = threeDigitsToWord(num%1000, count) + res;
            num /= 1000;
            count++;
        }

        res[res.size()-1] = '\0';

        return res;
    }
};
