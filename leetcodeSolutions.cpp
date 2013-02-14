/*
3Sum

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a <= b <= c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/
class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > v;
        int i, j, k, sum, n=num.size();
        sort(num.begin(),num.end());
        for(i=0;i<n-2;i++)
        {
            j=i+1;
            k=n-1;
            while(j<k)
            {
                sum=num[i]+num[j]+num[k];
                if(sum==0)
                {
                    vector<int> _v;
                    _v.push_back(num[i]);
                    _v.push_back(num[j]);
                    _v.push_back(num[k]);
                    if(find(v.begin(),v.end(),_v)==v.end())v.push_back(_v);
                    j++;
                    k--;
                }
                else if(sum>0)k--;
                else j++;
            }
        }
        return v;
    }
};

/*
3Sum Closest

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

*/
class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        int i, j, k, sum=0, n=num.size(), r=num[0]+num[1]+num[2];
        sort(num.begin(),num.end());
        for(i=0;i<n-2;i++)
        {
            j=i+1;
            k=n-1;
            while(j<k)
            {
                sum=num[i]+num[j]+num[k];
                if(sum==target)return sum;
                if(abs(sum-target)<abs(target-r))r=sum;
                if(sum>target)k--;
                else j++;
            }
        }
        return r;
    }
};

/*
4Sum

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

    Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a <= b <= c <= d)
    The solution set must not contain duplicate quadruplets.

    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/
// O(n^3) Solution
class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        int N=num.size();
        vector<vector<int> > quad;
        if(N<4)return quad;
        sort(num.begin(),num.end());
        int i,j,l,r,sum;
        for(i=0;i<N-3;i++)
        {
            for(j=i+1;j<N-2;j++)
            {
                l=j+1;r=N-1;
                while(l<r)
                {
                    sum=num[i]+num[j]+num[l]+num[r];
                    if(sum==target)
                    {
                        vector<int> _quad;
                        _quad.push_back(num[i]);
                        _quad.push_back(num[j]);
                        _quad.push_back(num[l]);
                        _quad.push_back(num[r]);
                        if(find(quad.begin(),quad.end(),_quad)==quad.end())quad.push_back(_quad);
                        l++;r--;
                    }
                    else if(sum<target)l++;
                    else r--;
                }
            }
        }
        return quad;
    }
};
// O(n^2 lg n)Solution
// http://www.codeproject.com/Articles/38381/STL-Sort-Comparison-Function
// http://www.cplusplus.com/reference/algorithm/sort/
class Solution {
public:
    struct twoSum
    {
        int i1, i2, data;
        twoSum(int i1, int i2, int data)
        {
            this->i1=i1;
            this->i2=i2;
            this->data=data;
        }
    };
    struct compareTwoSum
    {
        bool operator() (twoSum a, twoSum b)
        {
            if(a.data==b.data)
            {
                if(a.i1==b.i1)return a.i2<b.i2;
                else return a.i1<b.i1;
            }
            else return a.data<b.data;
        }
    } cts;
    // TLE for Large Cases if I give vector<int> v
    int beg(vector<twoSum> &v, int l, int r, int val)
    {
        int m;
        while(l<=r)
        {
            m=(l+r)>>1;
            if(val<=v[m].data)r=m-1;
            else l=m+1;
        }
        return r+1;
    }
    // TLE for Large Cases if I give vector<int> v
    int end(vector<twoSum> &v, int l, int r, int val)
    {
        int m;
        while(l<=r)
        {
            m=(l+r)>>1;
            if(val>=v[m].data)l=m+1;
            else r=m-1;
        }
        return l-1;
    }
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        vector<vector<int> > result;
        int n=num.size();
        if(n<4)return result;
        vector<twoSum> v;
        int i, j, lb, ub;
        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                v.push_back(twoSum(i,j,num[i]+num[j]));
            }
        }
        sort(v.begin(),v.end(),cts);
        n=v.size();
        for(i=0;i<n;i++)
        {
            lb=beg(v,i+1,n-1,target-v[i].data);
            ub=end(v,i+1,n-1,target-v[i].data);
            for(j=lb;j<=ub;j++)
            {
                if(v[j].i1==v[i].i1)continue;
                if(v[j].i2==v[i].i1)continue;
                if(v[j].i1==v[i].i2)continue;
                if(v[j].i2==v[i].i2)continue;
                vector<int> quad;
                quad.push_back(num[v[i].i1]);
                quad.push_back(num[v[i].i2]);
                quad.push_back(num[v[j].i1]);
                quad.push_back(num[v[j].i2]);
                sort(quad.begin(),quad.end());
                if(find(result.begin(),result.end(),quad)==result.end())result.push_back(quad);
            }
        }
        return result;
    }
};

/*
Add Binary

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
class Solution {
public:
    string addBinary(string a, string b) {
        int la=a.size()-1, lb=b.size()-1, sum=0;
        string r;
        while(la>=0 || lb>=0)
        {
           if(la>=0)sum+=a[la--]-48;
           if(lb>=0)sum+=b[lb--]-48;
           if(sum%2==1)r='1'+r;
           else r='0'+r;
           sum/=2;
        }
        if(sum)r='1'+r;
        return r;
    }
};

/*
Add Two Numbers

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *r=NULL;
        int sum=0;
        while(l1 || l2)
        {
            if(l1){sum+=l1->val;l1=l1->next;}
            if(l2){sum+=l2->val;l2=l2->next;}
            insert(&r,sum%10);
            sum/=10;
        }
        if(sum)insert(&r,sum);
        return r;
    }
    void insert(ListNode **head, int data)
    {
        while(*head)head=&(*head)->next;
        *head=new ListNode(data);
    }
};

/*Anagrams

Given an array of strings, return all groups of strings that are anagrams.

Note: All inputs will be in lower-case.
*/
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        map<string,vector<string> > m;
        map<string,vector<string> >::iterator im;
        vector<string> r;
        int i, n;
        for(i=strs.size()-1;i>=0;i--)
        {
            string s(strs[i]);
            sort(s.begin(),s.end());
            m[s].push_back(strs[i]);
        }
        for(im=m.begin();im!=m.end();im++)
        {
            n=(im->second).size();
            if(n>1)
            {
                for(i=0;i<n;i++)r.push_back((im->second)[i]);
                //r.insert(r.end(), im->second.begin(), im->second.end());
            }
        }
        return r;
    }
};

/*
Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
*/
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        int height=0;
        return isBalanced(root, height);
    }
    bool isBalanced(TreeNode *root, int &height)
    {
        if(!root){height--;return true;}
        int lh=height, rh=height;
        bool lb=isBalanced(root->left,lh);
        bool rb=isBalanced(root->right,rh);
        height=(lh>rh)?(1+lh):(1+rh);
        return (lb && rb && abs(lh-rh)<=1);
    }
};

/*
Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/
/*
http://www.leetcode.com/2010/11/best-time-to-buy-and-sell-stock.html
http://www.leetcode.com/2010/04/hacking-google-interview-from-mit.html
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int j=prices.size();
        if(j<2)return 0;
        int i, min=prices[0], profit=0;
        for(i=1;i<j;i++)
        {
            if(profit<prices[i]-min)profit=prices[i]-min;
            else if(prices[i]<min)min=prices[i];
        }
        return profit;
    }
};

/*
Best Time to Buy and Sell Stock II
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int j=prices.size(), profit=0;
        if(j<2)return profit;
        for(int i=0;i<j-1;i++)
        {
            if(prices[i+1]>prices[i])profit+=prices[i+1]-prices[i];
        }
        return profit;
    }
};

/*
Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n=prices.size();
        if(n<2)return 0;
        int *l=(int *)calloc(n,sizeof(int));
        int *r=(int *)calloc(n,sizeof(int));
        int i, profit=0, lmin=prices[0], rmax=prices[n-1];
        for(i=1;i<n;i++)
        {
            lmin=min(prices[i],lmin);
            l[i]=max(l[i-1],prices[i]-lmin);
        }
        for(i=n-2;i>=0;i--)
        {
            rmax=max(prices[i],rmax);
            r[i]=max(r[i+1],rmax-prices[i]);
        }
        for(i=0;i<n;i++)profit=max(profit,l[i]+r[i]);
        return profit;
    }
};

/*
Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> r;
        stack<TreeNode *> s;
        while(s.size() || root)
        {
            if(root)
            {
                s.push(root);
                root=root->left;
            }
            else

            {
                r.push_back((s.top())->val);
                root=(s.top())->right;
                s.pop();
            }
        }
        return r;
    }
};

/*
Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/
// Solution 1
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > r;
        vector<int> _r;
        queue<TreeNode *> q, _q;
        if(root)q.push(root);
        while(q.size())
        {
            while(q.size())
            {
                root=q.front();
                q.pop();
                if(root->left)_q.push(root->left);
                if(root->right)_q.push(root->right);
                _r.push_back(root->val);
            }
            swap(q,_q);
            r.push_back(_r);
            _r.clear();
        }
        return r;
    }
};
// Solution 2
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > r;
        vector<int> _r;
        queue<TreeNode *> q;
        int n;
        if(root)q.push(root);
        while(q.size())
        {
            n=q.size();
            while(n)
            {
                root=q.front();
                q.pop();
                if(root->left)q.push(root->left);
                if(root->right)q.push(root->right);
                _r.push_back(root->val);
                n--;
            }
            r.push_back(_r);
            _r.clear();
        }
        return r;
    }
};

/*
Binary Tree Level Order Traversal II
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7]
  [9,20],
  [3],
]
*/
/*
add these lines in place of return r; in previous code
        vector<vector<int> > res;
        for(int i=r.size()-1;i>=0;i--)res.push_back(r[i]);
        return res;
below is another possible solution
*/
class Solution {
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > r;
        vector<int> _r;
        if(!root)return r;
        for(int h=height(root);h>=1;h--)
        {
            get_r(root, h, _r);
            r.push_back(_r);
            _r.clear();
        }
        return r;
    }
    int height(TreeNode *root)
    {
        if(!root)return 0;
        return 1+max(height(root->left),height(root->right));
    }
    void get_r(TreeNode *n, int h, vector<int> &r)
    {
        if(!n)return;
        if(h==1){r.push_back(n->val);return;}
        get_r(n->left,h-1,r);
        get_r(n->right,h-1,r);
    }
};

/*
Binary Tree Maximum Path Sum

Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6.
*/
class Solution {
public:
    int help(TreeNode *root, int &maxSum)
    {
        if(!root)return 0;
        int sum=root->val;
        int leftMax=help(root->left,maxSum);
        int rightMax=help(root->right,maxSum);
        if(leftMax>0)sum+=leftMax;
        if(rightMax>0)sum+=rightMax;
        if(sum>maxSum)maxSum=sum;
        return max(root->val,root->val+max(leftMax,rightMax));
    }
    int maxPathSum(TreeNode *root) {
        if(!root)return 0;
        int maxSum=root->val;
        help(root,maxSum);
        return maxSum;
    }
};

/*
Binary Tree Zigzag Level Order Traversal
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
*/
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > r;
        vector<int> _r;
        if(!root)return r;
        for(int h=1;h<=height(root);h++)
        {
            if(h%2==1)get_lr(root,h,_r);
            else get_rl(root,h,_r);
            r.push_back(_r);
            _r.clear();
        }
        return r;
    }
    int height(TreeNode *root)
    {
        if(!root)return 0;
        return 1+max(height(root->left),height(root->right));
    }
    void get_lr(TreeNode *n, int h, vector<int> &r)
    {
        if(!n)return;
        if(h==1){r.push_back(n->val);return;}
        get_lr(n->left,h-1,r);
        get_lr(n->right,h-1,r);
    }
    void get_rl(TreeNode *n, int h, vector<int> &r)
    {
        if(!n)return;
        if(h==1){r.push_back(n->val);return;}
        get_rl(n->right,h-1,r);
        get_rl(n->left,h-1,r);
    }
};

/*
Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
class Solution {
public:
    int climbStairs(int n) {
        if(n<=2)return n;
        int a=1, b=2, c;
        while(n-->2)
        {
            c=a+b;
            a=b;
            b=c;
        }
        return c;
    }
};

/*
Combination Sum

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

    * All numbers (including target) will be positive integers.
    * Elements in a combination (a1, a2, ... , ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak).
    * The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
*/
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int> > r;
        sort(candidates.begin(),candidates.end());
        if(target<candidates[0])return r;
        vector<int> s;
        getCombination(candidates,r,target,0,s);
        return r;
    }
    void getCombination(vector<int> &c, vector<vector<int> > &r, int target, int i, vector<int> s)
    {
        if(target<0)return;
        if(target==0){
            if(find(r.begin(),r.end(),s)==r.end())r.push_back(s);
            return;
        }
        if(i==c.size())return;
        for(int j=0;j*c[i]<=target;j++)
        {
            if(j!=0)s.push_back(c[i]);
            getCombination(c,r,target-j*c[i],i+1,s);
        }
    }
};

/*
Combination Sum II

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

    * All numbers (including target) will be positive integers.
    * Elements in a combination (a1, a2, ... , ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak)
    * The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
*/
class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        vector<vector<int> > r;
        sort(num.begin(),num.end());
        if(target<num[0])return r;
        vector<int> s;
        getCombination(num,r,0,target,s);
        return r;
    }
    void getCombination(vector<int> &n, vector<vector<int> > &r, int i, int target, vector<int> s)
    {
        if(target<0)return;
        if(target==0)
        {
            if(find(r.begin(),r.end(),s)==r.end())r.push_back(s);
            return;
        }
        if(i==n.size())return;
        if(target<n[i])return;
        getCombination(n,r,i+1,target,s);
        s.push_back(n[i]);
        getCombination(n,r,i+1,target-n[i],s);
    }
};

/*
Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/
/*
// correct code is below this
// this code will generate all possible subsets
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > r;
        if(k>n)return r;
        vector<int> v;
        getCombination(1,n,k,r,v);
        return r;
    }
    void getCombination(int l, int n, int k, vector<vector<int> > &r, vector<int> v)
    {
        if(k==0)
        {
            r.push_back(v);
            return;
        }
        if(l>n)return;
        getCombination(l+1,n,k-1,r,v);
        v.push_back(l);
        getCombination(l+1,n,k-1,r,v);
    }
};
*/
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > r;
        if(k>n)return r;
        vector<int> v;
        getCombination(1,n,k,r,v);
        return r;
    }
    void getCombination(int l, int n, int k, vector<vector<int> > &r, vector<int> v)
    {
        if(k==v.size())
        {
            r.push_back(v);
            return;
        }
        if(l>n)return;
        getCombination(l+1,n,k,r,v);
        v.push_back(l);
        getCombination(l+1,n,k,r,v);
    }
};

/*
Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return buildTree(inorder.begin(),postorder.begin(),inorder.size());
    }
    TreeNode *buildTree(vector<int>::iterator i, vector<int>::iterator p, int n)
    {
        if(n==0)return NULL;
        int x=find(i,i+n,*(p+n-1))-i;
        TreeNode *r=new TreeNode(*(p+n-1));
        r->left=buildTree(i,p,x);
        r->right=buildTree(i+x+1,p+x,n-x-1);
        return r;
    }
};

/*
Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder.begin(),inorder.begin(),inorder.size());
    }
    TreeNode *buildTree(vector<int>::iterator p, vector<int>::iterator i, int n)
    {
        if(n==0)return NULL;
        int x=find(i,i+n,*p)-i;
        TreeNode *r=new TreeNode(*p);
        r->left=buildTree(p+1,i,x);
        r->right=buildTree(p+x+1,i+x+1,n-x-1);
        return r;
    }
};

/*
Container With Most Water

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.
*/
/*
// my first solution for which i got time limit exceeded
class Solution {
public:
    int maxArea(vector<int> &height) {
        int h, b, a=0, n=height.size();
        int i, j;
        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                h=min(height[i],height[j]);
                b=j-i;
                if(h*b>a)a=h*b;
            }
        }
        return a;
    }
};
*/
class Solution {
public:
    int maxArea(vector<int> &height) {
        int i=0, j=height.size()-1, h, a=0;
        while(i<j)
        {
            h=min(height[i],height[j]);
            if(a<h*(j-i))a=h*(j-i);
            if(height[i]==h)
            {
                i++;
                while(h>=height[i] && i<j)i++;
            }
            else
            {
                j--;
                while(h>=height[j] && i<j)j--;
            }
        }
        return a;
    }
};

/*
Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/
// solution 1
class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        return toBST(num, 0, num.size()-1);
    }
    TreeNode *toBST(vector<int> &n, int l, int r)
    {
        if(l>r)return NULL;
        int m=(l+r)>>1;
        TreeNode *root=new TreeNode(n[m]);
        root->left=toBST(n, l, m-1);
        root->right=toBST(n, m+1, r);
        return root;
    }
};
// solution 2
// in toBST function use vector<int> &n
// otherwise you may get MEMORY LIMIT EXCEEDED
class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        TreeNode *root=NULL;
        toBST(&root, num, 0, num.size()-1);
        return root;
    }
    void toBST(TreeNode **root, vector<int> &n, int l, int r)
    {
        if(l>r)return;
        int m=(l+r)>>1;
        *root=new TreeNode(n[m]);
        toBST(&(*root)->left,n,l,m-1);
        toBST(&(*root)->right,n,m+1,r);
    }
};

/*
Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// Solution 1 [ O(n) time and space ]
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        vector<int> num;
        while(head)
        {
            num.push_back(head->val);
            head=head->next;
        }
        return toBST(num, 0, num.size()-1);
    }
    TreeNode *toBST(vector<int> &n, int l, int r)
    {
        if(l>r)return NULL;
        int m=(l+r)>>1;
        TreeNode *root=new TreeNode(n[m]);
        root->left=toBST(n, l, m-1);
        root->right=toBST(n, m+1, r);
        return root;
    }
};
// Solution 2 [ O(n) time and constant space ]
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        int n=0;
        count(head,n);
        return toBST(head, 0, n-1);
    }
    void count(ListNode *head, int &n)
    {
        if(!head)return;
        while(head)n++,head=head->next;
    }
    TreeNode *toBST(ListNode *&head, int l, int r)
    {
        if(l>r)return NULL;
        int m=(l+r)>>1;
        TreeNode *nodeL=toBST(head,l,m-1);
        TreeNode *node=new TreeNode(head->val);
        node->left=nodeL;
        head=head->next;
        node->right=toBST(head,m+1,r);
        return node;
    }
};

/*
Count and Say

The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.
*/
class Solution {
public:
    string countAndSay(int n) {
        vector<string> r;
        r.push_back("1");
        int i=0, j, c;
        while(i<n)
        {
            stringstream s;
            for(j=0;j<r[i].size();j++)
            {
                c=1;
                while(r[i][j]==r[i][j+1]){c++;j++;}
                s<<c<<r[i][j];
            }
            r.push_back(s.str());
            i++;
        }
        return r[n-1];
    }
};

/*
Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/
// https://github.com/zwxxx/LeetCode/blob/master/Decode_Ways.cpp
// i have commented 2 else statements
// because calloc initialises them to 0
class Solution {
public:
    bool canDecode(string s)
    {
        int n;
        stringstream(s) >> n;
        if(s.size()==1)
        {
            if(n>=1 && n<=9)return true;
            else return false;
        }
        if(n>=10 && n<=26)return true;
        else return false;
    }
    int numDecodings(string s) {
        int N=s.size();
        if(s.empty())return 0;
        int *f=(int *)calloc(N+1,sizeof(int));
        f[0]=1;
        if(canDecode(s.substr(0,1)))f[1]=1;
        //else f[1]=0;
        bool a,b;
        for(int i=1;i<N;i++)
        {
            a=canDecode(s.substr(i-1,2));
            b=canDecode(s.substr(i,1));
            if(a && b)f[i+1]=f[i]+f[i-1];
            else if(!a && b)f[i+1]=f[i];
            else if(a && !b)f[i+1]=f[i-1];
            //else f[i+1]=0;
        }
        return f[N];
    }
};

/*
Distinct Subsequences

Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/
/*
// for JUDGE LARGE i got TIME LIMIT EXCEEDED
class Solution {
public:
    int numDistinct(string S, string T) {
        int r=0;
        if(S.size()<T.size())return r;
        string s;
        getTotal(S,T,r,s,0);
        return r;
    }
    void getTotal(string S, string T, int &r, string s, int i)
    {
        if(s.size()==T.size())
        {
            if(s==T)r++;
            return;
        }
        if(i==S.size())return;
        getTotal(S,T,r,s,i+1);
        getTotal(S,T,r,s+S[i],i+1);
    }
};
*/
class Solution {
public:
    int numDistinct(string S, string T) {
        int R=T.size(), C=S.size();
        int r, c, d[R+1][C+1];
        for(r=1;r<=R;r++)d[r][0]=0;
        for(c=0;c<=C;c++)d[0][c]=1;
        for(r=1;r<=R;r++)
        {
            for(c=1;c<=C;c++)
            {
                d[r][c]=d[r][c-1];
                if(T[r-1]==S[c-1])d[r][c]+=d[r-1][c-1];
            }
        }
        return d[R][C];
    }
};

/*
Divide Two Integers

Divide two integers without using multiplication, division and mod operator.
*/
class Solution {
public:
    int divide(int dividend, int divisor) {
        unsigned int num, den, quo=0, tmp;
        int sign=1, shift;
        if(dividend<0)num=-dividend,sign=-sign;
        else num=dividend;
        if(divisor<0)den=-divisor,sign=-sign;
        else den=divisor;
        while(num>=den)
        {
            tmp=den;
            shift=0;
            while((long long)tmp<<1<=num)tmp<<=1,shift++;
            quo|=1<<shift;
            num-=tmp;
        }
        return sign==-1?-quo:quo;
    }
};

/*
Edit Distance

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int R=word1.size(), C=word2.size();
        int r, c, d[R+1][C+1];
        for(r=0;r<=R;r++)d[r][0]=r;
        for(c=1;c<=C;c++)d[0][c]=c;
        for(r=1;r<=R;r++)
        {
            for(c=1;c<=C;c++)
            {
                if(word1[r-1]==word2[c-1])
                {
                    d[r][c]=d[r-1][c-1];
                }
                else
                {
                    d[r][c]=1+min(min(d[r-1][c],d[r-1][c-1]),d[r][c-1]);
                }
            }
        }
        return d[R][C];
    }
};

/*First Missing Positive

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        int i=0;
        while(i<n)
        {
            if(A[i]>=1 && A[i]<=n && A[i]!=i+1 && A[i]!=A[A[i]-1])swap(&A[i],&A[A[i]-1]);
            else i++;
        }
        for(i=0;i<n;i++)
        {
            if(A[i]!=i+1)break;
        }
        return i+1;
    }
    void swap(int *a, int *b)
    {
        *a=*a+*b;
        *b=*a-*b;
        *a=*a-*b;
    }
};

/*
Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:

   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

Hints:
If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.
*/
class Solution {
public:
    void flatten(TreeNode *root) {
        if(!root)return;
        stack<TreeNode *> s;
        TreeNode *top;
        s.push(root);
        root=NULL;
        while(!s.empty())
        {
            top=s.top();
            s.pop();
            if(top->right){s.push(top->right);top->right=NULL;}
            if(top->left){s.push(top->left);top->left=NULL;}
            if(!root)root=top;
            else
            {
                root->right=top;
                root=root->right;
            }
        }
    }
};

/*
Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"
*/
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> r;
        if(n==0)return r;
        gP(r,"",n,0,0);
        return r;
    }
    void gP(vector<string> &r, string s, int n, int o, int c)
    {
        if(o==n && c==n)
        {
            if(find(r.begin(),r.end(),s)==r.end())r.push_back(s);
            return;
        }
        if(o<n)gP(r,s+"(",n,o+1,c);
        if(o>c)gP(r,s+")",n,o,c+1);
    }
};

/*
Gray Code

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2

Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
*/
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> r;
        int i=1<<n, j;
        for(j=0;j<i;j++)
        {
            r.push_back((j>>1)^j);
        }
        return r;
    }
};

/*
Implement strStr()

Implement strStr().

Returns a pointer to the first occurrence of needle in haystack, or null if needle is not part of haystack.
*/
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        char *x=NULL;
        int h=strlen(haystack), n=strlen(needle), i, j, flag;
        for(i=0;i<h-n+1;i++)
        {
            flag=1;
            for(j=0;j<n;j++)
            {
                if(haystack[i+j]!=needle[j]){flag=0;break;}
            }
            if(flag){x=haystack+i;break;}
        }
        return x;
    }
};

/*
Insert Interval

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> r;
        vector<Interval>::iterator i;
        int flag=0;
        for(i=intervals.begin();i!=intervals.end();i++)
        {
            if((*i).start<=newInterval.end && (*i).end>=newInterval.start)
            {
                newInterval.start=(newInterval.start>(*i).start)?(*i).start:newInterval.start;
                newInterval.end=(newInterval.end>(*i).end)?newInterval.end:(*i).end;
                continue;
            }
            if(!flag && (*i).start>newInterval.end)
            {
                r.push_back(newInterval);
                flag=1;
            }
            r.push_back(*i);
        }
        if(!flag)r.push_back(newInterval);
        return r;
    }
};

/*
Integer to Roman

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/
class Solution {
public:
    string intToRoman(int num) {
        map<int,string> m;
        map<int,string>::reverse_iterator i;
        string s;
        m[1]="I";
        m[4]="IV";
        m[5]="V";
        m[9]="IX";
        m[10]="X";
        m[40]="XL";
        m[50]="L";
        m[90]="XC";
        m[100]="C";
        m[400]="CD";
        m[500]="D";
        m[900]="CM";
        m[1000]="M";
        for(i=m.rbegin();i!=m.rend();i++)
        {
            while(num>=i->first)
            {
                s+=i->second;
                num-=i->first;
            }
        }
        return s;
    }
};

/*
Interleaving String

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int R=s1.length(), C=s2.length(), r, c;
        if(R+C!=s3.length())return false;
        bool d[R+1][C+1];
        d[0][0]=true;
        for(r=1;r<=R;r++)d[r][0]=s1.substr(0,r).compare(s3.substr(0,r))==0;
        for(c=1;c<=C;c++)d[0][c]=s2.substr(0,c).compare(s3.substr(0,c))==0;
        for(r=1;r<=R;r++)
        {
            for(c=1;c<=C;c++)
            {
                d[r][c]=false;
                if(s1[r-1]==s3[r+c-1] && d[r-1][c])d[r][c]=true;
                if(s2[c-1]==s3[r+c-1] && d[r][c-1])d[r][c]=true;
            }
        }
        return d[R][C];
    }
};

/*
Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.
A = [3,2,1,0,4], return false.
*/
class Solution {
public:
    bool canJump(int A[], int n) {
        int i=0, next=0;
        while(i<=next)
        {
            if(next>=n-1)return true;
            next=next>i+A[i]?next:i+A[i];
            i++;
        }
        return false;
    }
};

/*
Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
class Solution {
public:
    int jump(int A[], int n) {
        int i, start=0, end=0, next=0, steps=0;
        for(end;end<n-1;end=next)
        {
            steps++;
            for(i=start;i<=end;i++)if(next<A[i]+i)next=A[i]+i;
            start=end+1;
            if(next<=end)return -1;
        }
        return steps;
    }
};

/*
Largest Rectangle in Histogram

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/
// https://github.com/zwxxx/LeetCode/blob/master/Largest_Rectangle_in_Histogram.cpp
// in "Maximal Rectangle" maximal() can be replaced by largestRectangleArea()
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        stack<int> s;
        int i, area=0, N=height.size();
        int *width=(int*)calloc(N,sizeof(int));
        for(i=0;i<N;i++)
        {
            while(s.size() && height[i]<=height[s.top()])s.pop();
            if(s.size())width[i]=i-s.top()-1;
            else width[i]=i;
            s.push(i);
        }
        while(s.size())s.pop();
        for(i=N-1;i>=0;i--)
        {
            while(s.size() && height[i]<=height[s.top()])s.pop();
            if(s.size())width[i]+=s.top()-i-1;
            else width[i]+=N-i-1;
            s.push(i);
        }
        for(i=0;i<N;i++)
        {
            if(area<height[i]*(width[i]+1))area=height[i]*(width[i]+1);
        }
        return area;
    }
};

/*
Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5.
*/
class Solution {
public:
    int lengthOfLastWord(const char *s) {
        int count=0;
        while(*s)s++;
        s--;
        while(*s==32)s--;
        while(*s && *s!=32)s--,count++;
        return count;
    }
};

/*
Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> p, r;
        p.push_back(" ");
        p.push_back("");
        p.push_back("abc");
        p.push_back("def");
        p.push_back("ghi");
        p.push_back("jkl");
        p.push_back("mno");
        p.push_back("pqrs");
        p.push_back("tuv");
        p.push_back("wxyz");
        generate(digits,p,r,"",0);
        return r;
    }
    void generate(string digits, vector<string> p, vector<string> &r, string s, int n)
    {
        if(s.size()==digits.size()){r.push_back(s);return;}
        int row=digits[n]-'0';
        for(int col=0;col<p[row].size();col++)
        {
            generate(digits,p,r,s+p[row][col],n+1);
        }
    }
};

/*
Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.
*/
class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        int x, i, N=strs.size();
        if(N==0)return "";
        string s(strs[0]);
        for(x=0;x<s.size();x++)
        {
            for(i=1;i<N;i++)
            {
                if(s[x]!=strs[i][x])return s.substr(0,x);
            }
        }
        return s;
    }
};

/*
Longest Palindromic Substring

Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/
// http://www.leetcode.com/2011/11/longest-palindromic-substring-part-i.html
// http://www.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
// http://blog.theliuy.com/2012/longest-palindromic-substring/
// Solution 1 [O(n^2) time]
class Solution {
public:
    string longestPalindrome(string s) {
        int N=s.size();
        if(N==0)return "";
        if(N==1)return s;
        int i,j,l,r,start=0,len,x=1;
        for(i=0;i<N;i++)
        {
            for(j=0;j<2;j++)
            {
                l=i-j;
                r=i+1;
                while(l>=0 && r<N && s[l]==s[r]){l--;r++;}
                l++;r--;
                len=r-l+1;
                if(len>x){x=len;start=l;}
            }
        }
        return s.substr(start,x);
    }
};
// Solution 2 [O(n) time :: Manacherâ€™s algorithm]
class Solution {
public:
    string longestPalindrome(string s) {
        int i,n=s.size();
        string S("$#");
        for(i=0;i<n;i++)
        {
            S+=s[i];
            S+='#';
        }
        int maxC=0, maxL=0, id=0, max=0, N=S.size();
        int *p=(int *)calloc(N,sizeof(int));
        for(i=0;i<N;i++)
        {
            if(max>i)
              p[i]=(p[2*id-i]<max-i)?p[2*id-i]:max-i;
            else
              p[i]=1;
            while(S[i+p[i]]==S[i-p[i]])p[i]++;
            if(max<i+p[i])
            {
                max=i+p[i];
                id=i;
            }
        }
        for(i=0;i<N;i++)
        {
            if(maxL<p[i]-1)
            {
                maxL=p[i]-1;
                maxC=i;
            }
        }
        return s.substr(maxC/2-maxL/2-maxL%2,maxL);
    }
};

/*
Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int r=0, N=s.size();
        if(N==0)return r;
        bool m[26]={false};
        int start=0, end=0;
        while(end<N)
        {
            if(m[s[end]-'a'])
            {
                r=max(r,end-start);
                while(s[start]!=s[end])m[s[start++]-'a']=false;
                start++;
                end++;
            }
            else
            {
                m[s[end]-'a']=true;
                end++;
            }
        }
        r=max(r,end-start);
        return r;
    }
};

/*
Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        int N=s.size(), r=0;
        if(N<2)return r;
        int stack=0, continuous=0,i;
        for(i=0;i<N;i++)
        {
            continuous++;
            stack+=(s[i]=='(')?1:-1;
            if(stack==0)
            {
                r=max(r,continuous);
            }
            else if(stack<0)
            {
                stack=0;
                continuous=0;
            }
        }
        stack=0;
        continuous=0;
        for(i=N-1;i>=0;i--)
        {
            continuous++;
            stack+=(s[i]==')')?1:-1;
            if(stack==0)
            {
                r=max(r,continuous);
            }
            else if(stack<0)
            {
                stack=0;
                continuous=0;
            }
        }
        return r;
    }
};

/*
Maximal Rectangle

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
*/
class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int R=matrix.size(),area=0;
        if(R==0)return area;
        int r,c,C=matrix[0].size();
        vector<vector<int> > v;
        for(r=0;r<R;r++)
        {
            vector<int> _v;
            for(c=0;c<C;c++)_v.push_back(matrix[r][c]-'0');
            v.push_back(_v);
        }
        for(r=1;r<R;r++)
        {
            for(c=0;c<C;c++)if(v[r][c])v[r][c]+=v[r-1][c];
        }
        for(r=0;r<R;r++)area=max(area,maximal(v[r]));
        return area;
    }
    int maximal(vector<int> v)
    {
        stack<int> s;
        int N=v.size(), i, count, area=0;
        for(i=0;i<N;i++)
        {
            if(s.empty() || v[i]>=s.top())s.push(v[i]);
            else
            {
                count=0;
                while(!s.empty() && v[i]<s.top())
                {
                    count++;
                    area=max(area,count*s.top());
                    s.pop();
                }
                for(;count>=0;count--)s.push(v[i]);
            }
        }
        count=0;
        while(!s.empty())
        {
            count++;
            area=max(area,count*s.top());
            s.pop();
        }
        return area;
    }
};

/*
Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
*/
class Solution {
public:
    int maxDepth(TreeNode *root) {
        if(!root)return 0;
        else return 1+max(maxDepth(root->left),maxDepth(root->right));
    }
};

/*
Maximum Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/
// O(n^3) solution :: Time Limit Exceeded for Large Case
class Solution {
public:
    int maxSubArray(int A[], int n) {
        if(n==0)return -1;
        int s=0,i,j,k,maxS=A[0];
        for(i=0;i<n;i++)
        {
            for(j=i;j<n;j++)
            {
                s=0;
                for(k=i;k<=j;k++)s+=A[k];
                if(s>maxS)maxS=s;
            }
        }
        return maxS;
    }
};
// O(n^2) solution
class Solution {
public:
    int maxSubArray(int A[], int n) {
        if(n==0)return -1;
        int s=0,i,j,maxS=A[0];
        for(i=0;i<n;i++)
        {
            s=0;
            for(j=i;j<n;j++)
            {
                s+=A[j];
                if(s>maxS)maxS=s;
            }
        }
        return maxS;
    }
};
// O(n) solution
class Solution {
public:
    int maxSubArray(int A[], int n) {
        if(n==0)return -1;
        int s=0,i,maxS=A[0];
        for(i=0;i<n;i++)
        {
            s+=A[i];
            if(A[i]>s)s=A[i];
            if(s>maxS)maxS=s;
        }
        return maxS;
    }
};
// Divide & Conquer
class Solution {
public:
    int maxSubArray(int A[], int n) {
        return maxDQ(A,0,n-1);
    }
    int maxDQ(int *A, int l, int r)
    {
        if(l>r)return INT_MIN;
        if(l==r)return A[l];
        int i,s=0,m=(l+r)>>1;
        int lmax=A[m],rmax=A[m];
        for(i=m;i>=l;i--)
           s+=A[i],lmax=max(s,lmax);
        s=0;
        for(i=m;i<=r;i++)
           s+=A[i],rmax=max(s,rmax);
        s=max(maxDQ(A,l,m-1),maxDQ(A,m+1,r));
        return max(s,lmax+rmax-A[m]);
    }
};

/*
Median of Two Sorted Arrays

There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/
// http://www.leetcode.com/2011/01/find-k-th-smallest-element-in-union-of.html
// http://www.leetcode.com/2011/03/median-of-two-sorted-arrays.html
// http://www.leetcode.com/2011/03/median-of-two-sorted-arrays.html#comment-1053
// http://ideone.com/FtqjM
class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        return help(A,m,B,n,max(0,(m-n)/2),min(m-1,(m+n)/2));
    }
    double help(int *a, int m, int *b, int n, int l, int r)
    {
        if(l>r)return help(b,n,a,m,max(0,(n-m)/2),min(n-1,(m+n)/2));
        int i=(l+r)/2;
        int j=(m+n)/2-i;
        int ai=(i==m)?INT_MAX:a[i];
        int bj=(j==n)?INT_MAX:b[j];
        int ai_1=(i==0)?INT_MIN:a[i-1];
        int bj_1=(j==0)?INT_MIN:b[j-1];
        if(ai<bj_1)return help(a,m,b,n,i+1,r);
        if(ai>bj)return help(a,m,b,n,l,i-1);
        if((m+n)%2)return ai;
        return (ai+max(ai_1,bj_1))/2.0;
    }
};

/*
Merge Intervals

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
*/
struct compare
{
    bool operator() (Interval i, Interval j)
    {
        return i.start<j.start;
    }
}c;
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        int N=intervals.size();
        vector<Interval> r;
        if(!N)return r;
        sort(intervals.begin(),intervals.end(),c);
        int i, s=intervals[0].start, e=intervals[0].end;
        for(i=1;i<N;i++)
        {
            if(e>=intervals[i].start)
            {
                if(intervals[i].end>e)e=intervals[i].end;
                continue;
            }
            r.push_back( Interval(s,e));
            s=intervals[i].start, e=intervals[i].end;
        }
        r.push_back( Interval(s,e));
        return r;
    }
};

/*
Merge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/
struct compareListNode
{
    // Arrange ListNodes in descending order
    // ListNode popped will be the smallest
    bool operator() ( ListNode *a,  ListNode *b)
    {
        return a->val>b->val;
    }
};
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int i;
        priority_queue<ListNode *, vector<ListNode *>, compareListNode> pq;
        for(i=0;i<lists.size();i++)
        {
            if(lists[i])pq.push(lists[i]);
        }
        if(pq.empty())return NULL;
        ListNode *head=pq.top();
        pq.pop();
        ListNode *node=head;
        if(node->next)pq.push(node->next);
        while(pq.size())
        {
            node->next=pq.top();
            pq.pop();
            node=node->next;
            if(node->next)pq.push(node->next);
        }
        return head;
    }
};

/*
Merge Sorted Array

Given two sorted integer arrays A and B, merge B into A as one sorted array.

Note:
You may assume that A has enough space to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
*/
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        int i=m-1, j=n-1, x=m+n-1;
        while(i>=0 && j>=0)
        {
            if(A[i]>B[j])A[x--]=A[i--];
            else A[x--]=B[j--];
        }
        while(j>=0)A[x--]=B[j--];
    }
};

/*
Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
*/
// without splicing
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *x=NULL;
        while(l1 || l2)
        {
            if(l1 && l2)
            {
                if(l1->val<l2->val)addAtEnd(&x,l1->val),l1=l1->next;
                else addAtEnd(&x,l2->val),l2=l2->next;
            }
            else if(l1)addAtEnd(&x,l1->val),l1=l1->next;
            else if(l2)addAtEnd(&x,l2->val),l2=l2->next;
        }
        return x;

    }
    void addAtEnd(ListNode **head, int val)
    {
        while(*head)head=&(*head)->next;
        *head=new ListNode(val);
    }
};
// splicing
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *head=NULL,*tail=NULL;
        while(l1 && l2)
        {
            if(l1->val<l2->val)
            {
                if(head)tail->next=l1,tail=tail->next;
                else head=l1,tail=l1;
                l1=l1->next;
            }
            else
            {
                if(head)tail->next=l2,tail=tail->next;
                else head=l2,tail=l2;
                l2=l2->next;
            }

        }
        if(l1)
        {
            if(head)tail->next=l1;
            else head=l1;

        }
        if(l2)
        {
            if(head)tail->next=l2;
            else head=l2;
        }
        return head;
    }
};

/*
Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
*/
class Solution {
public:
    int minDepth(TreeNode *root) {
        if(!root)return 0;
        if(!root->right && !root->left)return 1;
        int l=INT_MAX, r=INT_MAX;
        if(root->left)l=minDepth(root->left);
        if(root->right)r=minDepth(root->right);
        return 1+min(l,r);
    }
};

/*
Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        int R=grid.size(), C=grid[0].size();
        int r,c,d[R][C];
        d[0][0]=grid[0][0];
        for(r=1;r<R;r++)d[r][0]=d[r-1][0]+grid[r][0];
        for(c=1;c<C;c++)d[0][c]=d[0][c-1]+grid[0][c];
        for(r=1;r<R;r++)
        {
            for(c=1;c<C;c++)
            {
                d[r][c]=grid[r][c]+min(d[r-1][c],d[r][c-1]);
            }
        }
        return d[R-1][C-1];
    }
};

/*
Minimum Window Substring

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the emtpy string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/
class Solution {
public:
    string minWindow(string S, string T) {
        map<char,int> mS, mT;
        int end=0, start=0, rend, rstart=-1, len=0;
        for(end=0;end<T.size();end++)mT[T[end]]++;
        for(end=0;end<S.size();end++)
        {
            mS[S[end]]++;
            if(mS[S[end]]<=mT[S[end]])len++;
            while(len==T.size())
            {
                if(end-start<rend-rstart || rstart==-1)rstart=start,rend=end;
                mS[S[start]]--;
                if(mS[S[start]]<mT[S[start]])len--;
                start++;
            }
        }
        return (rstart==-1)?"":S.substr(rstart,rend-rstart+1);
    }
};

/*
Multiply Strings

Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/
// Incorrect Solution 1 [error for large cases]
class Solution {
public:
    string multiply(string num1, string num2) {
        int l1=num1.size()-1, l2=num2.size()-1;
        long long int x, carry=0, n=0;
        char *ch="0123456789";
        string r("");
        for(x=0;x<=l1;x++)n=n*10+(num1[x]-48);
        for(l2;l2>=0;l2--)
        {
            x=n*(num2[l2]-48)+carry;
            carry=x/10;
            r=ch[x%10]+r;
        }
        while(carry)
        {
            r=ch[carry%10]+r;
            carry/=10;
        }
        return r;
    }
};
// Solution 2
class Solution {
public:
    string multiply(string num1, string num2) {
        int l1=num1.size(), l2=num2.size(), sum, carry;
        string res;
        int *n=(int *)calloc(l1+l2,sizeof(int));
        for(l1=num1.size()-1;l1>=0;l1--)
        {
            for(l2=num2.size()-1,carry=0;l2>=0;l2--)
            {
                sum=carry+(num1[l1]-48)*(num2[l2]-48)+n[l1+l2+1];
                carry=sum/10;
                n[l1+l2+1]=sum%10;
            }
            n[l1+l2+1]=carry;
        }
        l1=0;
        while(l1<num1.size()+num2.size()-1 && n[l1]==0)l1++;
        while(l1<num1.size()+num2.size())res+=n[l1++]+48;
        return res;
    }
};

/*
N-Queens

The n-queens puzzle is the problem of placing n queens on an nÃ—n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        int *colForRow=(int *)calloc(n,sizeof(int));
        vector<vector<string> > r;
        place(0,colForRow,n,r);
        return r;
    }
    void place(int row, int *colForRow, int n, vector<vector<string> > &r)
    {
        if(row==n)
        {
            vector<string> _r;
            for(int r=0;r<n;r++)
            {
                string s(n,'.');
                s[colForRow[r]]='Q';
                _r.push_back(s);
            }
            r.push_back(_r);
            return;
        }
        for(int c=0;c<n;c++)
        {
            colForRow[row]=c;
            if(check(row,colForRow))
            {
                place(row+1,colForRow,n,r);
            }
        }
    }
    bool check(int row, int *colForRow)
    {
        for(int r=0, x;r<row;r++)
        {
            x=colForRow[row]-colForRow[r];
            if(x<0)x*=-1;
            if(x==0 || x==row-r)return false;
        }
        return true;
    }
};

/*
N-Queens II

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/
class Solution {
public:
    int totalNQueens(int n) {
        int total=0;
        int *colForRow=(int*)calloc(n,sizeof(int));
        place(0,n,colForRow,total);
        return total;
    }
    void place(int row, int n, int *colForRow, int &total)
    {
        if(row==n)
        {
            total++;
            return;
        }
        for(int c=0;c<n;c++)
        {
            colForRow[row]=c;
            if(check(row,colForRow))
            {
                place(row+1,n,colForRow,total);
            }
        }
    }
    bool check(int row, int *colForRow)
    {
        for(int r=0, x;r<row;r++)
        {
            x=colForRow[row]-colForRow[r];
            if(x<0)x*=-1;
            if(x==0 || x==row-r)return false;
        }
        return true;
    }
};

/*
Next Permutation

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 -> 1,3,2
3,2,1 -> 1,2,3
1,1,5 -> 1,5,1
*/
// this code can be used in ::
// [1] Permutation Sequence
// [2] Permutations
// [3] Permutations II
// Another variant of this question asked is "You have a number. Find the next higher number with same digits."
class Solution {
public:
    void nextPermutation(vector<int> &num) {
        int N=num.size();
        if(N<2)return;
        int i=N-2,j=N-1;
        while(num[i]>=num[i+1] && i>=0)i--;
        if(i==-1){reverse(num,0,N-1);return;}
        while(j>i && num[j]<=num[i])j--;
        swap(num[j],num[i]);
        reverse(num,i+1,N-1);
    }
    void reverse(vector<int> &num,int i, int j)
    {
        while(i<j)swap(num[i++],num[j--]);
    }
};

/*
Palindrome Number

Determine whether an integer is a palindrome. Do this without extra space.
Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/
// http://www.leetcode.com/2012/01/palindrome-number.html
// Solution 1 (slow)
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)return false;
        int r=0, y=x;
        while(y)
        {
            r=10*r+y%10;
            y/=10;
        }
        return r==x;
    }
};
// Solution 2 (fast)
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)return false;
        int h=1;
        while(x/h>9)h*=10;
        while(x)
        {
            if(x/h != x%10)return false;
            x=(x%h)/10;
            h/=100;
        }
        return true;
    }
};

/*
Partition List

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
// solution 1
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if(!head || !head->next)return head;
        ListNode *h=head, *r=head;
        int val,n=0;
        while(h)n++,h=h->next;
        while(n--)
        {
            if(head->val>=x)
            {
                h=head;
                val=head->val;
                while(h->next)h->val=h->next->val,h=h->next;
                h->val=val;
            }
            else head=head->next;
        }
        return r;
    }
};
// solution 2
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if(!head || !head->next)return head;
        ListNode *h=head, *r=head;
        int val,n=0;
        while(h)n++,h=h->next;
        while(n--)
        {
            if(head->val>=x)
            {
                h=head;
                while(h->next)h=h->next;
                h->next=new ListNode(head->val);
                h=head->next;
                head->val=h->val;
                head->next=h->next;
                delete h;
            }
            else head=head->next;
        }
        return r;
    }
};

/*
Pascal's Triangle

Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
// Solution 1
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > v;
        if(!numRows)return v;
        v.reserve(numRows);
        vector<int> _v;
        int i, j;
        for(i=0;i<numRows;i++)
        {
            for(j=1;j<i;j++)
            {
                _v[j]=v[i-1][j]+v[i-1][j-1];
            }
            _v.push_back(1);
            v.push_back(_v);
        }
        return v;
    }
};
// Solution 2
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > r;
        vector<int> _r;
        for(int i=0;i<numRows;i++)
        {
            _r.push_back(1);
            for(int j=i-1;j>0;j--)
            {
                _r[j]+=_r[j-1];
            }
            r.push_back(_r);
        }
        return r;
    }
};

/*
Pascal's Triangle II

Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?
*/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> v;
        v.reserve(rowIndex+1);
        int i, j;
        for(i=0;i<=rowIndex;i++)
        {
            v.push_back(1);
            for(j=i-1;j>0;j--)
            {
                v[j]+=v[j-1];
            }
        }
        return v;
    }
};

/*
Path Sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/
class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if(!root)return false;
        sum-=root->val;
        if(!root->left && !root->right)return (sum==0);
        return hasPathSum(root->left,sum) || hasPathSum(root->right,sum);
    }
};

/*
Path Sum II

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
*/
class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > r;
        vector<int> _r;
        findPaths(root,sum,r,_r);
        return r;
    }
    void findPaths(TreeNode *root, int sum, vector<vector<int> > &r, vector<int> _r)
    {
        if(!root)return;
        sum-=root->val;
        _r.push_back(root->val);
        if(!root->left && !root->right && !sum){r.push_back(_r);return;}
        findPaths(root->left,sum,r,_r);
        findPaths(root->right,sum,r,_r);
    }
};

/*
Permutation Sequence

The set [1,2,3, ... ,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

   1. "123"
   2. "132"
   3. "213"
   4. "231"
   5. "312"
   6. "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/
// Solution 1 [MLE for Large Cases]
class Solution {
public:
    string getPermutation(int n, int k) {
        string num("");
        vector<string> res;
        for(int i=49;i<=n+48;i++)num+=i;
        help(res,num,0);
        sort(res.begin(),res.end());
        return res[k-1];
    }
    void help(vector<string> &res, string &num, int level)
    {
        if(level==num.size())
        {
            res.push_back(num);
            return;
        }
        for(int j=level;j<num.size();j++)
        {
            swap(num[j],num[level]);
            help(res,num,level+1);
            swap(num[j],num[level]);
        }
    }
};
// Solution 2
class Solution {
public:
    string getPermutation(int n, int k) {
        string result("");
        vector<char> v;
        vector<char>::iterator iv;
        int i, j, f;
        for(i=49;i<=48+n;i++)v.push_back(i);
        for(i=1;i<=n;i++)
        {
            f=factorial(n-i);
            j=0;iv=v.begin();
            while(j*f<k)j++,iv++;
            j--;iv--;
            k-=j*f;
            result+=*iv;
            v.erase(iv);
        }
        return result;
    }
    int factorial(int n)
    {
        return n<2?1:n*factorial(n-1);
    }
};

/*
Permutations

Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > res;
        help(res,num,0);
        return res;
    }
    void help(vector<vector<int> > &res, vector<int> &num, int level)
    {
        if(level==num.size())
        {
            res.push_back(num);
            return;
        }
        for(int j=level;j<num.size();j++)
        {
            swap(num[level],num[j]);
            help(res,num,level+1);
            swap(num[level],num[j]);
        }
    }
};

/*
Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
*/
// Solution 1 [TLE for large cases]
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int> > res;
        help(res,num,0);
        return res;
    }
    void help(vector<vector<int> > &res, vector<int> &num, int level)
    {
        if(level==num.size())
        {
            if(find(res.begin(),res.end(),num)==res.end())res.push_back(num);
            return;
        }
        for(int j=level;j<num.size();j++)
        {
            swap(num[j],num[level]);
            help(res,num,level+1);
            swap(num[j],num[level]);
        }
    }
};
// Solution 2
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int> > r;
        do
        {
            r.push_back(num);
            nextPermutation(num);
        }while(find(r.begin(),r.end(),num)==r.end());
        // the while loop below takes less time to execute
        // while(!equal(r[0].begin(),r[0].end(),num.begin()));
        return r;
    }
    void nextPermutation(vector<int> &num) {
        int N=num.size();
        if(N<2)return;
        int i=N-2,j=N-1;
        while(num[i]>=num[i+1] && i>=0)i--;
        if(i==-1){reverse(num,0,N-1);return;}
        while(j>i && num[j]<=num[i])j--;
        swap(num[j],num[i]);
        reverse(num,i+1,N-1);
    }
    void reverse(vector<int> &num,int i, int j)
    {
        while(i<j)swap(num[i++],num[j--]);
    }
};

/*
Plus One

Given a number represented as an array of digits, plus one to the number.
*/
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int i,sum=1;
        reverse(digits.begin(),digits.end());
        for(i=0;i<digits.size();i++)
        {
            sum+=digits[i];
            if(sum)
            {
                digits[i]=sum%10;
                sum/=10;
            }
            else break;
        }
        if(sum)digits.push_back(sum);
        reverse(digits.begin(),digits.end());
        return digits;
    }
};

/*
Populating Next Right Pointers in Each Node

Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    * You may only use constant extra space.
    * You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/
// using DFS
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root)return;
        if(root->left)root->left->next=root->right;
        if(root->right && root->next)root->right->next=root->next->left;
        connect(root->left);
        connect(root->right);
    }
};
// using BFS
class Solution {
private:
    TreeLinkNode *node;
public:
    void connect(TreeLinkNode *root) {
        if(!root)return;
        node=root->left;
        while(root)
        {
            if(root->left)root->left->next=root->right;
            if(root->right && root->next)root->right->next=root->next->left;
            root=root->next;
        }
        connect(node);
    }
};

/*
Populating Next Right Pointers in Each Node II

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

    * You may only use constant extra space.

For example,
Given the following binary tree,

         1
       /  \
      2    3
     / \    \
    4   5    7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL

*/
class Solution {
private:
    TreeLinkNode *node;
public:
    void connect(TreeLinkNode *root) {
        if(!root)return;
        node=NULL;
        while(root)
        {
            if(root->left)root->left->next=root->right?root->right:getNextRight(root->next);
            if(root->right)root->right->next=getNextRight(root->next);
            if(!node)node=root->left?root->left:root->right;
            root=root->next;
        }
        connect(node);
    }
    TreeLinkNode *getNextRight(TreeLinkNode *n)
    {
        while(n)
        {
            if(n->left)return n->left;
            if(n->right)return n->right;
            n=n->next;
        }
        return NULL;
    }
};

/*
Pow(x, n)

Implement pow(x, n).
*/
class Solution {
public:
    double pow(double x, int n) {
        double y=1;
        int sign=1;
        if(n<0)sign=-sign,n=-n;
        for(;n>0;n/=2)
        {
            if(n%2)y*=x;
            x*=x;
        }
        return sign==1?y:1/y;
    }
};

/*
Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
*/
// Solution 1 [O(n) extra space]
class Solution {
public:
    void recoverTree(TreeNode *root) {
        vector<TreeNode *> v, s;
        int i, n;
        inorder(root,v);
        n=v.size();
        for(i=0;i<n-1;i++)
        {
            if(v[i]->val>v[i+1]->val){s.push_back(v[i]);break;}
        }
        for(i=n-1;i>0;i--)
        {
            if(v[i]->val<v[i-1]->val){s.push_back(v[i]);break;}
        }
        if(s.size()==2)swap(s[0]->val,s[1]->val);
    }
    void inorder(TreeNode *root, vector<TreeNode *> &v)
    {
        if(!root)return;
        inorder(root->left,v);
        v.push_back(root);
        inorder(root->right,v);
    }
};
// Solution 2 [constant space]
class Solution {
public:
    void recoverTree(TreeNode *root) {
        TreeNode *prev=NULL, *first=NULL, *second=NULL;
        inorder(root,prev,first,second);
        swap(first->val,second->val);
    }
    void inorder(TreeNode *root, TreeNode *&prev, TreeNode *&first, TreeNode *&second)
    {
        if(!root)return;
        inorder(root->left,prev,first,second);
        if(prev && prev->val>root->val)
        {
            if(!first)first=prev;
            second=root;
        }
        prev=root;
        inorder(root->right,prev,first,second);
    }
};

/*
Regular Expression Matching

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ? false
isMatch("aa","aa") ? true
isMatch("aaa","aa") ? false
isMatch("aa", "a*") ? true
isMatch("aa", ".*") ? true
isMatch("ab", ".*") ? true
isMatch("aab", "c*a*b") ? true
*/
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if(*p=='\0')return *p==*s;
        if(*(p+1)!='*')
        {
            return (*p==*s || (*p=='.' && *s!='\0')) && isMatch(s+1,p+1);
        }
        while(*p==*s || (*p=='.' && *s!='\0'))
        {
            if(isMatch(s,p+2))return true;
            s++;
        }
        return isMatch(s,p+2);
    }
};

/*
Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array A = [1,1,2],

Your function should return length = 2, and A is now [1,2].
*/
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n<2)return n;
        int i=1, j=1;
        while(i<n)
        {
            if(A[i-1]==A[i])i++;
            else A[j++]=A[i++];
        }
        return j;
    }
};

/*
Remove Duplicates from Sorted Array II

Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array A = [1,1,1,2,2,3],

Your function should return length = 5, and A is now [1,1,2,2,3].
*/
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int i=0, j=0, count=0;
        while(i<n)
        {
            if(i==0 || A[i]==A[i-1])count++;
            else count=1;
            if(count<=2)A[j++]=A[i++];
            else i++;
        }
        return j;
    }
};

/*
Remove Duplicates from Sorted List

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if(!head)return head;
        ListNode *node=head, *tmp;
        while(node->next)
        {
            if(node->val==node->next->val)
            {
                tmp=node->next;
                node->next=tmp->next;
                delete tmp;
            }
            else node=node->next;
        }
        return head;
    }
};

/*
Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if(!head)return head;
        ListNode *node=head, *tmp;
        while(node->next)
        {
            if(node->val==node->next->val)
            {
                while(node->next && node->val==node->next->val)
                {
                    tmp=node->next;
                    node->next=tmp->next;
                    delete tmp;
                }
                if(node->next)
                {
                    tmp=node->next;
                    node->val=tmp->val;
                    node->next=tmp->next;
                    delete tmp;
                }
                else
                {
                    if(head==node)
                    {
                        delete head;
                        head=NULL;
                        return head;
                    }
                    tmp=head;
                    while(tmp->next!=node)tmp=tmp->next;
                    tmp->next=NULL;
                    delete node;
                    return head;
                }
            }
            else node=node->next;
        }
        return head;
    }
};

/*
Remove Element

Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.
*/
class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        if(n<1)return n;
        int i=0;
        n--;
        while(i<=n)
        {
            if(A[i]==elem)A[i]=A[n--];
            else i++;
        }
        return i;
    }
};

/*
Remove Nth Node From End of List

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass.
*/
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if(!head)return head;
        ListNode *l=head, *r=head;
        while(--n)r=r->next;
        while(r->next)r=r->next,l=l->next;
        if(!l->next)
        {
            if(l==head)return NULL;
            l=head;
            while(l->next!=r)l=l->next;
            r->val=l->val;
        }
        r=l->next;
        l->val=r->val;
        l->next=r->next;
        delete r;
        return head;
    }
};

/*
Restore IP Addresses

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> r;
        if(s.size()>=4 && s.size()<=12)ipHelp(s,0,0,"",r);
        return r;
    }
    void ipHelp(string s, int i, int p, string _s, vector<string> &r)
    {
        if(p>4)return;
        if(i==s.size())
        {
            if(p==4)r.push_back(_s);
            return;
        }
        int x=0, j=i;
        while(j<s.size())
        {
            x=10*x+(s[j]-'0');
            if(x>255)return;
            if(p && i==j)_s+=".";
            _s+=s[j++];
            ipHelp(s,j,p+1,_s,r);
            if(!x)break;
        }
    }
};

/*
Reverse Integer

Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.
Have you thought about this?

Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

Throw an exception? Good, but what if throwing an exception is not an option? You would then have to re-design the function (ie, add an extra parameter).
*/
class Solution {
public:
    int reverse(int x) {
        int r=0;
        while(x)
        {
            r=10*r+x%10;
            x/=10;
        }
        return r;
    }
};

/*
Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 <= m <= n <= length of list.
*/
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if(!head || !head->next)return head;
        ListNode *preTail=NULL, *curTail=NULL;
        ListNode *preNode=NULL, *curNode=head, *node;
        for(int i=1;i<=n;i++)
        {
            if(i==m-1)preTail=curNode;
            if(i==m)curTail=curNode;
            if(i>=m)
            {
                node=curNode->next;
                curNode->next=preNode;
                preNode=curNode;
                curNode=node;
            }
            else curNode=curNode->next;
        }
        if(!preTail)head=preNode;
        else preTail->next=preNode;
        curTail->next=curNode;
        return head;
    }
};

/*
Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(!head || k<2)return head;
        ListNode *rhead, *rnode, *rtail, *cur, *_head;
        int n=0,i;
        rhead=new ListNode(0);
        rhead->next=head;
        _head=rhead;
        while(head)n++,head=head->next;
        n/=k;
        while(n--)
        {
            rtail=rhead->next;
            cur=rtail->next;
            for(i=1;i<k;i++)
            {
                rnode=cur;
                cur=cur->next;
                rtail->next=rnode->next;
                rnode->next=rhead->next;
                rhead->next=rnode;
            }
            rhead=rtail;
        }
        head=_head->next;
        delete _head;
        return head;
    }
};

/*
Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.
*/
class Solution {
public:
    int romanToInt(string s) {
        map<char,int> m;
        m['M']=1000;
        m['D']=500;
        m['C']=100;
        m['L']=50;
        m['X']=10;
        m['V']=5;
        m['I']=1;
        int r=0, i;
        for(i=0;i<s.size()-1;i++)
        {
            if(m[s[i]]<m[s[i+1]])r-=m[s[i]];
            else r+=m[s[i]];
        }
        r+=m[s[i]];
        return r;
    }
};

/*
Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int r, c, tmp, N=matrix.size();
        for(r=0;r<N/2;r++)
        {
            for(c=r;c<N-r-1;c++)
            {
                tmp=matrix[r][c];
                matrix[r][c]=matrix[N-1-c][r];
                matrix[N-1-c][r]=matrix[N-1-r][N-1-c];
                matrix[N-1-r][N-1-c]=matrix[c][N-1-r];
                matrix[c][N-1-r]=tmp;
            }
        }
    }
};

/*
Rotate List

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if(!head)return head;
        int n=0;
        ListNode *l=head, *r=head;
        while(l)l=l->next,n++;
        k%=n;
        l=r;
        while(k--)r=r->next;
        while(r->next)r=r->next,l=l->next;
        r->next=head;
        head=l->next;
        l->next=NULL;
        return head;
    }
};

/*
Same Tree

Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
*/
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(!p || !q)return p==q;
        // Logical AND has left-to-right associativity.
        // The second operand is evaluated only if the first operand evaluates to true (nonzero).
        return p->val==q->val && isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
    }
};


/*
Scramble String

Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \

  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
*/
// logic for i=2
// s1 :: great
// s2 :: rgtae
// (s1,l1,l1+i,s2,l2,l2+i) for gr in s1 and rg in s2
// (s1,l1+i,u1,s2,l2+i,u2) for eat in s1 and tae in s2
// s1 :: great
// s2 :: taerg
// (s1,l1,l1+i,s2,u2-i,u2) for gr in s1 and rg in s2
// (s1,l1+i,u1,s2,l2,u2-i) for eat in s1 and tae in s2
// Solution 1
class Solution {
public:
    bool isScramble(string s1, string s2) {
        return helpScramble(s1,0,s1.size(),s2,0,s2.size());
    }
    bool helpScramble(string &s1, int l1, int u1, string &s2, int l2, int u2)
    {
        if( !same(s1.substr(l1,u1-l1),s2.substr(l2,u2-l2)) )return false;
        if(l1==u1-1)return true;
        for(int i=1;i<u1-l1;i++)
        {
            if( ( helpScramble(s1,l1,l1+i,s2,l2,l2+i) && helpScramble(s1,l1+i,u1,s2,l2+i,u2) )
                ||
                ( helpScramble(s1,l1,l1+i,s2,u2-i,u2) && helpScramble(s1,l1+i,u1,s2,l2,u2-i) ) )return true;
        }
        return false;
    }
    bool same(string s1, string s2)
    {
        sort(s1.begin(),s1.end());
        sort(s2.begin(),s2.end());
        return s1==s2;
    }
};
// Solution 2
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(!same(s1,s2))return false;
        if(s1.size()<2)return true;
        int n=s1.size();
        for(int i=1;i<n;i++)
        {
            if( ( isScramble(s1.substr(0,i),s2.substr(0,i)) && isScramble(s1.substr(i,n-i),s2.substr(i,n-i)) )
                ||
                ( isScramble(s1.substr(0,i),s2.substr(n-i,i)) && isScramble(s1.substr(i,n-i),s2.substr(0,n-i)) ) )return true;
        }
        return false;
    }
    bool same(string s1, string s2)
    {
        sort(s1.begin(),s1.end());
        sort(s2.begin(),s2.end());
        return s1==s2;
    }
};

/*
Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    * Integers in each row are sorted from left to right.
    * The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return true.
*/
// Solution 1
// correct but won't work for
// { {10, 20, 30, 40}, {15, 25, 35, 45}, {27, 29, 37, 48} }
// i.e. when 1st integer of row < last integer of the previous row
// i discuss this because the questions are very close
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int R=matrix.size();
        int C=R?matrix[0].size():0;
        int lb=0, ub=R*C-1, mid, r, c;
        while(lb<=ub)
        {
            mid=(lb+ub)>>1;
            r=mid/C;
            c=mid%C;
            if(target==matrix[r][c])return true;
            if(target<matrix[r][c])ub=mid-1;
            else lb=mid+1;
        }
        return false;
    }
};
// Solution 2
// works for both cases
// (a) as asked in question [[1,3,5,7],[10,11,16,20],[23,30,34,50]]
// (b) for array above { {10, 20, 30, 40}, {15, 25, 35, 45}, {27, 29, 37, 48} }
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int R=matrix.size();
        int C=R?matrix[0].size():0;
        int r=0, c=C-1;
        while(r<R && c>=0)
        {
            if(target==matrix[r][c])return true;
            if(target<matrix[r][c])c--;
            else r++;
        }
        return false;
    }
};

/*
Search for a Range

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/
class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> res;
        int l=-1, r=-1, lb, ub, mid;
        // finding start of interval
        lb=0;ub=n-1;
        while(lb<=ub)
        {
            mid=(lb+ub)>>1;
            if(target==A[mid])l=mid,ub=mid-1;
            else if(target<A[mid])ub=mid-1;
            else lb=mid+1;
        }
        // finding end of interval
        lb=0;ub=n-1;
        while(lb<=ub)
        {
            mid=(lb+ub)>>1;
            if(target==A[mid])r=mid,lb=mid+1;
            else if(target<A[mid])ub=mid-1;
            else lb=mid+1;
        }
        res.push_back(l);
        res.push_back(r);
        return res;
    }
};

/*
Search in Rotated Sorted Array

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/
class Solution {
public:
    int search(int A[], int n, int target) {
        int l=0, r=n-1, m;
        while(l<=r)
        {
            m=(l+r)>>1;
            if(A[m]==target)return m;
            if(A[l]<=A[m])
            {
                if(A[l]<=target && target<A[m])r=m-1;
                else l=m+1;
            }
            else
            {
                if(A[m]<target && target<=A[r])l=m+1;
                else r=m-1;
            }
        }
        return -1;
    }
};

/*
Search in Rotated Sorted Array II

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
class Solution {
public:
    bool search(int A[], int n, int target) {
        int i=0;
        while(i<n)
        {
            if(A[i]==target)return true;
            i++;
        }
        return false;
    }
};

/*
Search Insert Position

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 => 2
[1,3,5,6], 2 => 1
[1,3,5,6], 7 => 4
[1,3,5,6], 0 => 0
*/
class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        int l=0, r=n-1, m;
        while(l<=r)
        {
            m=(l+r)>>1;
            if(A[m]==target)return m;
            if(target<A[m])r=m-1;
            else l=m+1;
        }
        return l;
    }
};

/*
Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
*/
// O(m+n) solution
class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        int R=matrix.size();
        int C=R?matrix[0].size():0;
        int r, c;
        vector<int> row(R,0), col;
        //row.resize(R);
        col.resize(C);
        for(r=0;r<R;r++)
        {
            for(c=0;c<C;c++)
            {
                if(!matrix[r][c])row[r]=1,col[c]=1;
            }
        }
        for(r=0;r<R;r++)
        {
            for(c=0;c<C;c++)
            {
                if(row[r] || col[c])matrix[r][c]=0;
            }
        }
    }
};
// constant space solution
class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        int R=matrix.size(), C=R?matrix[0].size():0;
        int r, c, x=0, y=0;
        for(r=0;r<R;r++)if(!matrix[r][0])y=1;
        for(c=0;c<C;c++)if(!matrix[0][c])x=1;
        for(r=1;r<R;r++)
        {
            for(c=1;c<C;c++)
            {
                if(!matrix[r][c])matrix[r][0]=0,matrix[0][c]=0;
            }
        }
        for(r=1;r<R;r++)
        {
            if(!matrix[r][0])
            {
                for(c=1;c<C;c++)matrix[r][c]=0;
            }
        }
        for(c=1;c<C;c++)
        {
            if(!matrix[0][c])
            {
                for(r=1;r<R;r++)matrix[r][c]=0;
            }
        }
        if(x)
        {
            for(c=0;c<C;c++)matrix[0][c]=0;
        }
        if(y)
        {
            for(r=0;r<R;r++)matrix[r][0]=0;
        }
    }
};

/*
Simplify Path

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/

/*
Sort Colors

Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.
*/
// Solution 1
class Solution {
public:
    void sortColors(int A[], int n) {
        int color[3]={0};
        for(n--;n>=0;n--)color[A[n]]++;
        while(color[0]--)A[++n]=0;
        while(color[1]--)A[++n]=1;
        while(color[2]--)A[++n]=2;
    }
};
// Solution 2
class Solution {
public:
    void sortColors(int A[], int n) {
        int l=0, m=0, r=n-1;
        while(m<=r)
        {
            if(A[m]==0)
            {
                A[m++]=A[l];
                A[l++]=0;
            }
            else if(A[m]==1)
            {
                m++;
            }
            else
            {
                A[m]=A[r];
                A[r--]=2;
            }
        }
    }
};

/*
Spiral Matrix

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

You should return [1,2,3,6,9,8,7,4,5].
*/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        int R=matrix.size(), C=R?matrix[0].size():0;
        vector<int> res;
        int i, r=0, c=0;
        while(r<R && c<C)
        {
            for(i=c;i<C;i++)res.push_back(matrix[r][i]);
            r++;
            C--;
            for(i=r;i<R;i++)res.push_back(matrix[i][C]);
            if(r<R)
            {
                R--;
                for(i=C-1;i>=c;i--)res.push_back(matrix[R][i]);
            }
            if(c<C)
            {
                for(i=R-1;i>=r;i--)res.push_back(matrix[i][c]);
                c++;
            }
        }
        return res;
    }
};

/*
Spiral Matrix II

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,
You should return the following matrix:

[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int> > res;
        int i, r=0, c=0, R=n, C=n, x=1;
        for(i=0;i<n;i++)res.push_back(vector<int>(n,0));
        while(r<R && c<C)
        {
            for(i=c;i<C;i++)res[r][i]=x++;
            r++;
            C--;
            for(i=r;i<R;i++)res[i][C]=x++;
            if(r<R)
            {
                R--;
                for(i=C-1;i>=c;i--)res[R][i]=x++;
            }
            if(c<C)
            {
                for(i=R-1;i>=r;i--)res[i][c]=x++;
                c++;
            }
        }
        return res;
    }
};

/*
Sqrt(x)

Implement int sqrt(int x).

Compute and return the square root of x.
*/
// Solution 1 [slow]
class Solution {
public:
    int sqrt(int x) {
        long long i=0;
        while(true)
        {
            if((i+1)*(i+1)>x)break;
            i++;
        }
        return (int)i;
    }
};
// Solution 2 [fast]
class Solution {
public:
    int sqrt(int x) {
        if(x<2)return x;
        long long l=0, m, r=1+x/2;
        while(l<r-1)
        {
            m=(l+r)>>1;
            if(m*m==x)return m;
            if(m*m<x)l=m;
            else r=m;
        }
        return (int)l;
    }
};

/*
String to Integer (atoi)

Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.
*/
class Solution {
public:
    int atoi(const char *str) {
        long long res=0;
        int sign=1;
        while(*str==32)str++;
        if(*str=='+')str++;
        if(*str=='-')sign=-1,str++;
        while(*str>=48 && *str<=57)
        {
            res=10*res+(*str-48);
            str++;
        }
        res*=sign;
        if(res<INT_MIN)res=INT_MIN;
        if(res>INT_MAX)res=INT_MAX;
        return (int)res;
    }
};

/*
Subsets

Given a set of distinct integers, S, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If S = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/
// Solution 1 [binary number conversion]
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        int i, j, k, n=1<<S.size();
        vector<vector<int> > r;
        vector<int> _r;
        sort(S.begin(),S.end());
        for(i=0; i<n;i++)
        {
            j=i;
            k=0;
            _r.clear();
            while(j)
            {
                if(j & 0x1)_r.push_back(S[k]);
                j>>=1;
                k++;
            }
            r.push_back(_r);
        }
        return r;
    }
};
// Solution 2 [recursion]
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > r;
        vector<int> _r;
        sort(S.begin(),S.end());
        help(0,_r,r,S);
        return r;
    }
    void help(int level, vector<int> &_r, vector<vector<int> > &r, vector<int> &S)
    {
        if(level==S.size())
        {
            r.push_back(_r);
            return;
        }
        help(level+1,_r,r,S);
        _r.push_back(S[level]);
        help(level+1,_r,r,S);
        //_r.resize(_r.size()-1);
        _r.pop_back();
    }
};

/*
Subsets II

Given a collection of integers that might contain duplicates, S, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If S = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/
// Solution 1 [binary number conversion]
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        int i, j, k, n=1<<S.size();
        vector<vector<int> > r;
        vector<int> _r;
        sort(S.begin(),S.end());
        for(i=0; i<n;i++)
        {
            j=i;
            k=0;
            _r.clear();
            while(j)
            {
                if(j & 0x1)_r.push_back(S[k]);
                j>>=1;
                k++;
            }
            if(find(r.begin(),r.end(),_r)==r.end())r.push_back(_r);
        }
        return r;
    }
};
// Solution 2 [recursion]
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > r;
        vector<int> _r;
        sort(S.begin(),S.end());
        help(0,_r,r,S);
        return r;
    }
    void help(int level, vector<int> &_r, vector<vector<int> > &r, vector<int> &S)
    {
        if(level==S.size())
        {
            if(find(r.begin(),r.end(),_r)==r.end())r.push_back(_r);
            return;
        }
        help(level+1,_r,r,S);
        _r.push_back(S[level]);
        help(level+1,_r,r,S);
        //_r.resize(_r.size()-1);
        _r.pop_back();
    }
};

/*
Substring with Concatenation of All Words

You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

For example, given:
S: "barfoothefoobarman"
L: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/
class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        vector<int> r;
        map<string,int> mL;
        map<string,int> m;
        string s;
        int i, j, k, nS=S.size(), nL=L.size(), len=L[0].size();
        for(i=0;i<nL;i++)mL[L[i]]++;
        for(i=0;i<=nS-nL*len;i++)
        {
            m.clear();
            for(j=0;j<nL;j++)
            {
                k=i+j*len;
                s=S.substr(k,len);
                if(mL.find(s)==mL.end())break;
                m[s]++;
                if(m[s]>mL[s])break;
            }
            if(j==nL)r.push_back(i);
        }
        return r;
    }
};

/*
Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/
class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
        list<int> dots;
        int r, c;
        for(r=0;r<9;r++)
        {
            for(c=0;c<9;c++)
            {
                if(board[r][c]=='.')dots.push_back(r*9+c);
            }
        }
        bool a=help(board,dots);
    }
    bool help(vector<vector<char> > &board, list<int> &dots)
    {
        if(!dots.size())return true;
        bool possible[10];
        int i, j, head=dots.front(), x=head/9, y=head%9, x_, y_;
        // possible[0] won't be required
        for(i=0;i<10;i++)possible[i]=true;
        // if a number is present in that row/column, leave it
        for(i=0;i<9;i++)
        {
            if(board[x][i]!='.')possible[board[x][i]-48]=false;
            if(board[i][y]!='.')possible[board[i][y]-48]=false;
        }
        // if a number is present in 3x3 sub-square, leave it
        for(i=0, x_=x/3*3, y_=y/3*3; i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(board[x_+i][y_+j]!='.')possible[board[x_+i][y_+j]-48]=false;
            }
        }
        // try out the numbers that you have now
        for(i=1;i<10;i++)
        {
            if(possible[i])
            {
                dots.pop_front();
                board[x][y]=i+48;
                if(help(board,dots))return true;
                dots.push_front(head);
                board[x][y]='.';
            }
        }
        return false;
    }
};

/*
Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/
// Solution 1 [swapping values]
class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        if(!head || !head->next)return head;
        ListNode *l1=head, *l2=head->next;
        while(l2)
        {
            swap(l1->val,l2->val);
            l1=l2->next;
            l2=l1?l1->next:NULL;
        }
        return head;
    }
};
// Solution 2 [one pass - changing links]
class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode *prev=NULL, *cur=head, *next;
        while(cur)
        {
            next=cur->next;
            if(!next)return head;
            if(!prev)head=next;
            else prev->next=next;
            cur->next=next->next;
            next->next=cur;
            prev=cur;
            cur=cur->next;
        }
        return head;
    }
};

/*
Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3

Note:
Bonus points if you could solve it both recursively and iteratively.
*/
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if(!root)return true;
        return help(root->left,root->right);
    }
    bool help(TreeNode *l, TreeNode *r)
    {
        if(!l || !r)return l==r;
        return l->val==r->val && help(l->left,r->right) && help(l->right,r->left);
    }
};

/*
Text Justification

Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Note: Each word is guaranteed not to exceed L in length.
Corner Cases:

    A line other than the last line might contain only one word. What should you do in this case?
    In this case, that line should be left-justified.
*/
class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> r;
        if(L<1){r.push_back("");return r;}
        int n=words.size(), l, i, spQ, spR, beg=0, end;
        string space;
        while(beg<n)
        {
            l=0;
            end=beg;
            while(end<n)
            {
                l+=words[end].size();
                if(l<=L)l++,end++;
                else {l-=words[end].size();break;}
            }
            end--;
            space="";
            l-=end-beg+1;
            if(beg==end || end==n-1)
            {
                // left justified
                for(i=beg;i<end;i++)space+=words[i]+" ";
                space+=words[end];
                for(i=1;i<=L-l-(end-beg);i++)space+=" ";
                r.push_back(space);
            }
            else
            {
                // spaces in between
                spQ=(L-l)/(end-beg);
                spR=(L-l)%(end-beg);
                while(beg<end)
                {
                    space+=words[beg++];
                    for(i=1;i<=spQ;i++)space+=" ";
                    if(spR)spR--,space+=" ";
                }
                space+=words[beg];
                r.push_back(space);
            }
            beg=end+1;
        }
        return r;
    }
};

/*
Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*/
class Solution {
public:
    int trap(int A[], int n) {
        int *lr=(int *)calloc(n,sizeof(int));
        int *rl=(int *)calloc(n,sizeof(int));
        int i, j, r=0;
        for(lr[0]=A[0],i=1;i<n;i++)lr[i]=(A[i]>lr[i-1])?A[i]:lr[i-1];
        for(rl[n-1]=A[n-1],i=n-2;i>=0;i--)rl[i]=(A[i]>rl[i+1])?A[i]:rl[i+1];
        for(i=1;i<n-1;i++)
        {
            j=(lr[i-1]<rl[i+1])?lr[i-1]:rl[i+1];
            r+=(j>A[i])?j-A[i]:0;
        }
        return r;
    }
};

/*
Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int i, j, n=triangle.size();
        for(i=n-2;i>=0;i--)
        {
            for(j=0;j<=i;j++)
            {
                triangle[i][j]+=min(triangle[i+1][j],triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};

/*
Two Sum

Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/
// Solution 1 [little slow]
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> r;
        int i;
        for(i=0;i<numbers.size();i++)
        {
            if( find(numbers.begin()+i+1,numbers.end(),target-numbers[i]) != numbers.end() )
            {
                r.push_back(i+1);
                r.push_back(1+find(numbers.begin()+i+1,numbers.end(),target-numbers[i])-numbers.begin());
                break;
            }
        }
        return r;
    }
};
// Solution 2 [faster .. because of map/hashing]
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int,int> m;
        vector<int> r;
        for(int i=0;i<numbers.size();i++)
        {
            if(m.find(target-numbers[i])==m.end())
            {
                m[numbers[i]]=i+1;
            }
            else
            {
                if(i+1<m[target-numbers[i]])
                {
                    r.push_back(i+1);
                    r.push_back(m[target-numbers[i]]);
                }
                else
                {
                    r.push_back(m[target-numbers[i]]);
                    r.push_back(i+1);
                }
                break;
            }
        }
        return r;
    }
};

/*
Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/
// Solution 1 [recursion]
class Solution {
public:
    int numTrees(int n) {
        if(n<2)return 1;
        int i, s=0;
        for(i=0;i<n;i++)s+=numTrees(i)*numTrees(n-i-1);
        return s;
    }
};
// Solution 2 [dynamic programming]
class Solution {
public:
    int numTrees(int n) {
        if(n<2)return 1;
        int i, j;
        int *dp=(int*)calloc(n+1,sizeof(int));
        dp[0]=1;dp[1]=1;
        for(i=2;i<=n;i++)
        {
            for(j=0;j<i;j++)
            {
                dp[i]+=dp[j]*dp[i-j-1];
            }
        }
        return dp[n];
    }
};

/*
Unique Binary Search Trees II

Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        return help(1,n);
    }
    vector<TreeNode *> help(int l, int r)
    {
        vector<TreeNode *> root;
        if(l>r)
        {
            root.push_back(NULL);
            return root;
        }
        for(int i=l;i<=r;i++)
        {
            vector<TreeNode *> left=help(l,i-1);
            vector<TreeNode *> right=help(i+1,r);
            for(int j=0;j<left.size();j++)
            {
                for(int k=0;k<right.size();k++)
                {
                    TreeNode *node=new TreeNode(i);
                    node->left=left[j];
                    node->right=right[k];
                    root.push_back(node);
                }
            }
        }
        return root;
    }
};

/*
Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
Note: m and n will be at most 100.
*/
// Solution 1 [recursive .. TLE for Large Cases]
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int> > grid(m,vector<int> (n,0));
        int paths=0;
        help(0,0,m,n,paths,grid);
        return paths;
    }
    void help(int r, int c, int m, int n, int &paths, vector<vector<int> > &grid)
    {
        if(r==m-1 && c==n-1)
        {
            paths++;
            return;
        }
        grid[r][c]=1;
        if(r<m-1)help(r+1,c,m,n,paths,grid);
        if(c<n-1)help(r,c+1,m,n,paths,grid);
        grid[r][c]=0;
    }
};
// Solution 2 [DP]
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int> > grid(m,vector<int> (n,0));
        int r, c;
        for(r=0;r<m;r++)grid[r][0]=1;
        for(c=0;c<n;c++)grid[0][c]=1;
        for(r=1;r<m;r++)
        {
            for(c=1;c<n;c++)
            {
                grid[r][c]=grid[r][c-1]+grid[r-1][c];
            }
        }
        return grid[m-1][n-1];
    }
};
// Solution 3 [DP .. space optimised]
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> grid(n,1);
        int r, c;
        for(r=1;r<m;r++)
        {
            for(c=1;c<n;c++)
            {
                grid[c]+=grid[c-1];
            }
        }
        return grid[n-1];
    }
};

/*
Unique Paths II

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,

There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]

The total number of unique paths is 2.

Note: m and n will be at most 100.
*/
// Solution 1 [recursive .. TLE for Large Cases]
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int m=obstacleGrid.size(), n=m?obstacleGrid[0].size():0;
        int paths=0;
        help(0,0,m,n,paths,obstacleGrid);
        return paths;
    }
    void help(int r, int c, int m, int n, int &paths, vector<vector<int> >

&obstacleGrid)
    {
        if(obstacleGrid[r][c])return;
        if(r==m-1 && c==n-1)
        {
            paths++;
            return;
        }
        obstacleGrid[r][c]=1;
        if(r<m-1)help(r+1,c,m,n,paths,obstacleGrid);
        if(c<n-1)help(r,c+1,m,n,paths,obstacleGrid);
        obstacleGrid[r][c]=0;
    }
};
// Solution 2 [DP]
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int m=obstacleGrid.size(), n=m?obstacleGrid[0].size():0;
        vector<vector<int> > grid(m,vector<int> (n,0));
        int r, c;
        grid[0][0]=obstacleGrid[0][0]?0:1;
        for(r=1;r<m;r++)grid[r][0]=obstacleGrid[r][0]?0:grid[r-1][0];
        for(c=1;c<n;c++)grid[0][c]=obstacleGrid[0][c]?0:grid[0][c-1];
        for(r=1;r<m;r++)
        {
            for(c=1;c<n;c++)
            {
                grid[r][c]=obstacleGrid[r][c]?0:grid[r-1][c]+grid[r][c-1];
            }
        }
        return grid[m-1][n-1];
    }
};
// Solution 3 [DP .. space optimised]
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int m=obstacleGrid.size(), n=m?obstacleGrid[0].size():0;
        vector<int> dp(n,0);
        int r, c;
        dp[0]=obstacleGrid[0][0]?0:1;
        for(r=0;r<m;r++)
        {
            for(c=0;c<n;c++)
            {
                if(obstacleGrid[r][c])
                {
                    dp[c]=0;
                }
                else dp[c]+=c?dp[c-1]:0;
            }
        }
        return dp[n-1];
    }
};

/*
Valid Number

Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
*/

/*
Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
*/
class Solution {
public:
    bool isPalindrome(string s) {
        int N=s.size();
        int l=0, r=N-1;
        char lb, ub;
        while(l<r)
        {
            lb=s[l]>=65 && s[l]<=90?s[l]+32:s[l];
            ub=s[r]>=65 && s[r]<=90?s[r]+32:s[r];
            if(!( (lb>=97 && lb<=122)||(lb>=48 && lb<=57) ))
            {
                l++;
                continue;
            }
            if(!( (ub>=97 && ub<=122)||(ub>=48 && ub<=57) ))
            {
                r--;
                continue;
            }
            if(lb!=ub)return false;
            l++,r--;
        }
        return true;
    }
};

/*
Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
class Solution {
public:
    bool isValid(string s) {
        stack<char> stak;
        char c,_c;
        for(int i=0;i<s.size();i++)
        {
            _c=s[i];
            if(_c=='(' || _c=='{' || _c=='[')stak.push(_c);
            else
            {
                if(stak.empty())return false;
                c=stak.top();
                stak.pop();
                if(
                    (c=='(' && _c!=')')||
                    (c=='{' && _c!='}')||
                    (c=='[' && _c!=']')
                   )return false;
            }
        }
        if(stak.size())return false;
        return true;
    }
};

/*
Valid Sudoku

Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
A partially filled sudoku which is valid.
*/
class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        bool n[10];
        int r, c, i, r_, c_;
        for(r=0;r<9;r++)
        {
            memset(n,0,sizeof(n));
            for(c=0;c<9;c++)
            {
                if(board[r][c]!='.')
                {
                    if(n[board[r][c]-48])return false;
                    n[board[r][c]-48]=true;
                }
            }
        }
        for(r=0;r<9;r++)
        {
            memset(n,0,sizeof(n));
            for(c=0;c<9;c++)
            {
                if(board[c][r]!='.')
                {
                    if(n[board[c][r]-48])return false;
                    n[board[c][r]-48]=true;
                }
            }
        }
        for(i=0;i<9;i++)
        {
            memset(n,0,sizeof(n));
            r_=i/3*3;c_=i%3*3;
            for(r=0;r<3;r++)
            {
                for(c=0;c<3;c++)
                {
                    if(board[r_+r][c_+c]!='.')
                    {
                        if(n[board[r_+r][c_+c]-48])return false;
                        n[board[r_+r][c_+c]-48]=true;
                    }
                }
            }
        }
        return true;
    }
};

/*
Validate Binary Search Tree

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.
*/
// Solution 1 [preorder O(n)]
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        return help(root, INT_MIN, INT_MAX);
    }
    bool help(TreeNode *root, int min, int max)
    {
        if(!root)return true;
        return min<root->val &&
               max>root->val &&
               help(root->left, min, root->val) &&
               help(root->right, root->val, max);
    }
};
// Solution 2 [inorder O(n)]
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        int min=INT_MIN;
        return help(root,min);
    }
    bool help(TreeNode *root, int &min)
    {
        if(!root)return true;
        if(help(root->left,min))
        {
            if(min<root->val)
            {
                min=root->val;
                return help(root->right,min);
            }
            else return false;
        }
        else return false;
    }
};
// Solution 3 [inorder O(n)]
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        TreeNode *prev=NULL, *first=NULL;
        inorder(root,prev,first);
        return first?false:true;
    }
    void inorder(TreeNode *root, TreeNode *&prev, TreeNode *&first)
    {
        if(!root)return;
        inorder(root->left,prev,first);
        if(prev && prev->val>=root->val)first=prev;
        prev=root;
        inorder(root->right,prev,first);
    }
};

/*
Wildcard Matching

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") => false
isMatch("aa","aa") => true
isMatch("aaa","aa") => false
isMatch("aa", "*") => true
isMatch("aa", "a*") => true
isMatch("ab", "?*") => true
isMatch("aab", "c*a*b") => false
*/

/*
Word Search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        int R=board.size(), C=R?board[0].size():0, L=word.size();
        int r, c;
        vector<vector<bool> > visited(R,vector<bool> (C,false));
        for(r=0;r<R;r++)
        {
            for(c=0;c<C;c++)
            {
                if(help(board,word,visited,r,c,0,R,C,L))return true;
            }
        }
        return false;
    }
    bool help(vector<vector<char> > &board, string &word, vector<vector<bool> > &visited,  int r, int c, int l, int R, int C, int L)
    {
        if(r<0 || r>=R || c<0 || c>=C)return false;
        if(visited[r][c])return false;
        if(word[l]!=board[r][c])return false;
        if(l+1==L)return true;
        visited[r][c]=true;
        if( help(board,word,visited,r-1,c,l+1,R,C,L) ||
            help(board,word,visited,r,c-1,l+1,R,C,L) ||
            help(board,word,visited,r+1,c,l+1,R,C,L) ||
            help(board,word,visited,r,c+1,l+1,R,C,L) )return true;
        visited[r][c]=false;
        return false;
    }
};

/*
ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/
// Solution 1
class Solution {
public:
    string convert(string s, int nRows) {
        if(nRows<2)return s;
        string r;
        vector<string> x(nRows,"");
        int i, n=0;
        while(s[n])
        {
            for(i=0;i<nRows-1;i++)
            {
                if(s[n])x[i]+=s[n++];
                else break;
            }
            for(i;i>=1;i--)
            {
                if(s[n])x[i]+=s[n++];
                else break;
            }
        }
        for(i=1;i<nRows;i++)x[0]+=x[i];
        return x[0];
    }
};
// Solution 2
class Solution {
public:
    string convert(string s, int nRows) {
        if(nRows<2)return s;
        int i, j, k, _k=nRows*2-2, n=s.size();
        string r("");
        for(i=0;i<nRows;i++)
        {
            k= (i==nRows-1) ? _k : 2*i ;
            for(j=i;j<n;j+=k)
            {
                r+=s[j];
                if(_k-k)k=_k-k;
            }
        }
        return r;
    }
};
