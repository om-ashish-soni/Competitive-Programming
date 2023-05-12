// problem link : https://leetcode.com/problems/4sum-ii/description/
// solution : below code

class Solution {
public:
    void buildmap(vector<int> & v1,vector<int> & v2,unordered_map<long long,long long> & mp){
        for(int i=0;i<v1.size();i++){
            long long first=v1[i];
            for(int j=0;j<v2.size();j++){
                long long second=v2[j];
                long long key=first+second;                
                mp[key]++;
            }
        }
        // for(auto & pr:mp){
        //     cout<<pr.first<<" , "<<pr.second<<" } ";
        // }
        // cout<<endl;
    }
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<long long,long long> mp1,mp2;
        buildmap(nums1,nums2,mp1);
        buildmap(nums3,nums4,mp2);
        long long ctr=0;
        
        for(auto & pr:mp1){
            long long key1=pr.first;
            long long freq1=pr.second;
            long long key2=-key1;
            if(mp2.count(key2)){
                // cout<<key1<<" , "<<key2<<" :: "<<freq1<<" , "<<freq1<<endl;
                long long freq2=mp2[key2];
                ctr+=freq1*freq2;
            }
        }
        return ctr;
    }
};