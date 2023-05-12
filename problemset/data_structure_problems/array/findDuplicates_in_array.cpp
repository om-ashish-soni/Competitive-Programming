class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int,int> freq;
        int occurance;
        
        for(auto num:nums){
            occurance=++freq[num];
            if(occurance-1) return num;
        }
        return occurance;//this will not be executed any more
    }
};