// Problem link : https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// Problem type : binary search
class Solution {
public:
    int binarySearch(vector<int> &arr, int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}
 
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size()==0){
            return *new vector<int>(2,-1);
        }
        int left=-1,right=-1;
        int end=nums.size()-1;
        int pos=binarySearch(nums,0,end,target);
        cout<<pos<<endl;
        vector<int> v(2);
        if(pos==-1){
            v[0]=v[1]=-1;
            return v;
        }else{
            left=right=pos;
            while(pos != -1){
                cout<<"in left "<<pos<<endl;
                left=pos;
                pos=binarySearch(nums,0,pos-1,target);
            }
            v[0]=left;
            pos=right;
            while(pos != -1){
                cout<<"in right "<<pos<<endl;
                right=pos;
                pos=binarySearch(nums,pos+1,end,target);
            }
            v[1]=right;
        }
        return v;
    }
};
