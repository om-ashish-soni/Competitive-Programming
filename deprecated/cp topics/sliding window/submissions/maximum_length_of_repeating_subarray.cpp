// problem link : https://leetcode.com/problems/maximum-length-of-repeated-subarray/
// solution : below code

class Solution {
public:
    int dothis(vector<int>& nums1, vector<int>& nums2){
        int n=nums1.size();
        int m=nums2.size();
        int mx=0;
        for(int i=0;i<m;i++){
            int li=i;
            int last=0;
            // cout<<"start : "<<i<<endl;
            for(int j=0;i<m && j<n;i++,j++){
                // cout<<"comparing : "<<i<<" with "<<j<<" : "<<nums2[i]<<" <=> "<<nums1[j]<<endl;
                if(nums2[i]==nums1[j]){
                    last++;
                }else{
                    mx=max(mx,last);
                    last=0;
                }
            }
            mx=max(mx,last);
            i=li;
            // cout<<"i : "<<i<<endl;
        }
        return mx;
    }
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int first=dothis(nums1,nums2);
        int second=dothis(nums2,nums1);
        return max(first,second);
    }
};
