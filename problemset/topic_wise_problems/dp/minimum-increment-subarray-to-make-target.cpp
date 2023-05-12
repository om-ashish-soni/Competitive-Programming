// problem link : https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/description/
// solution : below code

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n=target.size();
        int last=0;
        int ctr=0; 
        for(int i=0;i<n;i++){
            int num=target[i];
            if(last<num){
                ctr+=num-last;
            }
            last=num;
        }
        return ctr;
    }
};