// problem link : https://leetcode.com/problems/find-longest-awesome-substring/description/
// solution : below code

class Solution {
public:

    int longestAwesome(string s) {
        string key="0000000000";
        unordered_map<string,int> mp;
        mp[key]=-1;
        int mx=0;
        int i=-1;
        for(auto c:s){
            ++i;
            int index=c-'0';
            key[index]^=1;
            vector<string> perms;
            perms.push_back(key);
            for(int i=0;i<key.size();i++){
                string key_i=key;
                key_i[i]^=1;
                perms.push_back(key_i);
            }
            int mn=i;
            for(auto & key_i:perms){
                if(mp.count(key_i)) mn=min(mn,mp[key_i]);
            }
            int diff=(i-mn);
            mx=max(mx,diff);
            if(mp.count(key)==0)mp[key]=i;
        }
        return mx;
    }
};