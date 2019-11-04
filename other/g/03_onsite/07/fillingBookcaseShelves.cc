/*

https://leetcode.com/problems/filling-bookcase-shelves/

We have a sequence of books: the i-th book has thickness books[i][0] and height books[i][1].

We want to place these books in order onto bookcase shelves that have total width shelf_width.

We choose some of the books to place on this shelf (such that the sum of their thickness is <= shelf_width), then build another level of shelf of the bookcase so that the total height of the bookcase has increased by the maximum height of the books we just put down.  We repeat this process until there are no more books to place.

Note again that at each step of the above process, the order of the books we place is the same order as the given sequence of books.  For example, if we have an ordered list of 5 books, we might place the first and second book onto the first shelf, the third book on the second shelf, and the fourth and fifth book on the last shelf.

Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.



Example 1:


Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelf_width = 4
Output: 6
Explanation:
The sum of the heights of the 3 shelves are 1 + 3 + 2 = 6.
Notice that book number 2 does not have to be on the first shelf.


Constraints:

1 <= books.length <= 1000
1 <= books[i][0] <= shelf_width <= 1000
1 <= books[i][1] <= 1000

*/

/*
https://leetcode.com/problems/filling-bookcase-shelves/discuss/323473/cpp%2Bdp%2B1043

Refer :: Partition Array for Maximum Sum
https://leetcode.com/problems/partition-array-for-maximum-sum/
and
https://leetcode.com/problems/partition-array-for-maximum-sum/discuss/291057/Java-visualize-the-pattern
for better understanding

*/

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        int i, j, N=books.size(), width, height;
        vector<int> dp(N+1, INT_MAX);

        dp[0] = 0;

        for(i=1; i<=N; i++) {
            height = books[i-1][1];
            width = 0;
            for(j=i-1; j>=0; j--) {
                height = max(height, books[j][1]);
                width += books[j][0];
                if(width > shelf_width) {
                    break;
                }
                dp[i] = min(dp[i], dp[j]+height);
            }
        }

        return dp[N];
    }
};


/*
// Partition Array for Maximum Sum
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int i, j, N=A.size(), maxNum;
        vector<int> dp(N+1, 0);

        for(i=1; i<=N; i++) {
            maxNum = A[i-1];
            for(j=i-1; j>=0 && j>=i-K; j--) {
                maxNum = max(maxNum, A[j]);
                dp[i] = max(dp[i], dp[j]+(i-j)*maxNum);
            }
        }

        return dp[N];
    }
};
*/
