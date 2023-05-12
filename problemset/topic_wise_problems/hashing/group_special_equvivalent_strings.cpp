// problem link : https://leetcode.com/problems/groups-of-special-equivalent-strings/description/
// solution : below code

class Solution {
public:
    int ctoi(char c){
        return c-'a';
    }
    vector<vector<int>> hashify(string & s){
        vector<vector<int>> hash(2,vector<int>(26,0));
        int n=s.size();
        for(int i=0;i<n;i++){
            // cout<<i%2<<" "<<ctoi(s[i])<<endl;
            hash[i%2][ctoi(s[i])]++;
        }
        return hash;
    }
    int numSpecialEquivGroups(vector<string>& words) {
        map<vector<vector<int>>,int> mp;
        for(auto & word:words){
            mp[hashify(word)]++;
        }
        return mp.size();
    }
};