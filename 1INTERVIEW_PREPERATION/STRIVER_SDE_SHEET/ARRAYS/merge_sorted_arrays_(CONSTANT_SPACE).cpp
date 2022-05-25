// problem link : https://leetcode.com/problems/merge-sorted-array/
// solution : below code

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tz=nums1.size();
        for(int i=tz-1;i>=n;i--){
            nums1[i]=nums1[i-n];
        }
        vector<int>& a=nums1;
        vector<int>& b=nums2;
        int ai=n,bi=0;
        int index=0;
        while(ai<tz && bi<n){
            if(a[ai]<b[bi]){
                nums1[index]=a[ai];
                ai++;
            }else{
                nums1[index]=b[bi];
                bi++;
            }
            index++;
        }
        while(ai<tz){
            nums1[index]=a[ai];
            ai++;index++;
        }
        while(bi<n){
            nums1[index]=b[bi];
            bi++;index++;
        }
        return ;
    }
};
