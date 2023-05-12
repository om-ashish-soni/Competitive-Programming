// problem link : https://leetcode.com/problems/longest-nice-subarray/
// solution : below code

class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int l=0;
        vi v(32,0);
        int key=0;
        int n=nums.size();
        int mx=0;
        F(i,0,n){
            key=(key | nums[i]);
            bitset<32> bs(nums[i]);
            int pick=0;
            F(k,0,32){
                if(bs[k]==1) v[k]++;
                pick=max(pick,v[k]);
            }
            
            while(pick>=2 && l<i){
                bitset<32> mybs(nums[l]);
                pick=0;
                F(k,0,32){
                    if(mybs[k]==1) v[k]--;
                    pick=max(pick,v[k]);
                }
                l++;
            }
            mx=max(mx,i-l+1);
        }
        return mx;
    }
};
