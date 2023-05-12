// problem link : https://leetcode.com/problems/permutation-in-string/description/
// solution : below code


class Solution {
public:
    int ctoi(char c){
        return c-'a';
    }
    void hashify(string & s,vector<int>& v){
        for(auto & c:s){
            v[ctoi(c)]++;
        }
    }
    void print(vector<int> & v){
        for(auto num:v) cout<<num<<" ";cout<<endl;
    }
    vector<int> difference(vector<int> & v1,vector<int> & v2){
        int n=v1.size();
        vector<int> v=v1;
        for(int i=0;i<n;i++){
            v[i]-=v2[i];
        }
        return v;
    }
    
    bool checkInclusion(string p, string s) {
        vector<int> v(26,0);
        map<vector<int>,int> mp;
        mp[v]=-1;
        vector<int> vp(26,0);
        hashify(p,vp);
        vector<int> op;
        for(int i=0;i<s.size();i++){
            v[ctoi(s[i])]++;
            vector<int> delta=difference(v,vp);
            if(mp.count(delta)){
                return true;
            }
            mp[v]=i;
        }
        return false;
    }
};