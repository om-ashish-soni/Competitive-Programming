// problem link : https://leetcode.com/problems/missing-number/
// solution : below code

#define ll long long
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        ll n=nums.size();
        ll sm=accumulate(begin(nums),end(nums),0LL);
        ll total=(n*(n+1))/2;
        return total-sm;
    }
};
