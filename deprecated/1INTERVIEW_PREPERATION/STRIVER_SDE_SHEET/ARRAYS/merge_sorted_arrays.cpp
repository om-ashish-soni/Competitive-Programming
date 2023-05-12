// problem link : https://leetcode.com/problems/merge-sorted-array/
// solution : below code

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> a=nums1;
        vector<int>& b=nums2;
        int ai=0,bi=0;
        int index=0;
        while(ai<m && bi<n){
            if(a[ai]<b[bi]){
                nums1[index]=a[ai];
                ai++;
            }else{
                nums1[index]=b[bi];
                bi++;
            }
            index++;
        }
        while(ai<m){
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
