// problem link : https://leetcode.com/problems/find-greatest-common-divisor-of-array/description/
// solution : below code

class Solution {
public:
    int gcd(int a,int b){
        if(b==0) return a;
        return gcd(b,a%b);
    }
    int findGCD(vector<int>& nums) {
        int mn=INT_MAX;
        int mx=INT_MIN;
        for(auto num:nums){
            mn=min(mn,num);
            mx=max(mx,num);
        }
        int hcf=gcd(mn,mx);
        return hcf;
    }
};