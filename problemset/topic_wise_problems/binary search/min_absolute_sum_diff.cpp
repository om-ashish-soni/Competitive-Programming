// problem link : https://leetcode.com/problems/minimum-absolute-sum-difference/description/
// solution : below code

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        vector<int> v=nums1;
        sort(v.begin(),v.end());
        int n=v.size();
        const int mod=1e9+7;
        long long cost=0;
        for(int i=0;i<n;i++){
            cost+=abs(nums1[i]-nums2[i]);
        }
        cout<<"cost : "<<cost<<endl;
        int mx=0;
        for(int i=0;i<n;i++){
            int key=nums2[i];
            int second=lower_bound(v.begin(),v.end(),key)-v.begin();
            int first=second-1;
            int mydiff=abs(nums1[i]-nums2[i]);
            int gift=0;
            if(first>=0){
                int delta=abs(key-v[first]);
                gift=max(gift,mydiff-delta);
            }
            if(second<n){
                int delta=abs(key-v[second]);
                gift=max(gift,mydiff-delta);
            }
            cout<<"i : "<<i<<" , gift : "<<gift<<endl;
            mx=max(mx,gift);
        }
        cost-=mx;
        return cost%mod;
    }
};