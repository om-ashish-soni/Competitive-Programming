// problem link : https://leetcode.com/problems/permutations/
//solution : below code
class Solution {
public:
    void permute(vector<int>& v,int index,vector<vector<int>>& soln){
        if(index>=v.size()-1){
            soln.push_back(v);   
            return;
        }
        permute(v,index+1,soln);
        for(int next=index+1;next<v.size();next++){
            swap(v[index],v[next]);
            permute(v,index+1,soln);            
            swap(v[index],v[next]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> soln;
        permute(nums,0,soln);
        return soln;
    }
};
