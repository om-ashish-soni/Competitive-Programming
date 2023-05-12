// problem link : https://leetcode.com/problems/sum-of-even-numbers-after-queries/
// solution : below code


class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int sm=0;
        vi v;
        FEACH(num,nums){
            if(num%2==0) sm+=num;    
        }
        FEACH(row,queries){
            int val=row[0];
            int index=row[1];
            if(nums[index]%2){
                if(val%2){
                    sm+=nums[index]+val;
                }
            }else{
                if(val%2==0){
                    sm+=val;
                }else{
                    sm-=nums[index];
                }
            }
            nums[index]+=val;
            v.pb(sm);
        }
        return v;
    }
};
