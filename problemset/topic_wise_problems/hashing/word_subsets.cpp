// problem link : https://leetcode.com/problems/word-subsets/
// solution : below code

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        map<char,int> mp;
        int m=words2.size();
        for(int i=0;i<m;i++){
            string & s=words2[i];
            map<char,int> cmap;
            for(auto c:s){
                cmap[c]++;
            }
            for(auto & pr:cmap){
                int key=pr.first;
                int freq=pr.second;
                mp[key]=max(mp[key],freq);
            }
        }
        vector<string> uni;
        for(auto & word:words1){
            map<char,int> cmap;
            for(auto c:word){
                cmap[c]++;
            }
            bool take=true;
            for(auto & pr:mp){
                if(cmap.count(pr.first) && cmap[pr.first]>=pr.second){
                    ;
                }else{
                    take=false;
                    break;
                }
            }
            if(take) uni.push_back(word);
        }
        return uni;
    }
};