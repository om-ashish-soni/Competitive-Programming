// problem link : https://leetcode.com/problems/find-all-anagrams-in-a-string/description/
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
    vector<int> findAnagrams(string s, string p) {
        vector<int> v(26,0);
        map<vector<int>,int> mp;
        mp[v]=-1;
        vector<int> vp(26,0);
        hashify(p,vp);
        vector<int> op;
        // cout<<"vp : ";print(vp);
        for(int i=0;i<s.size();i++){
            cout<<"index : "<<i<<endl;
            v[ctoi(s[i])]++;
            vector<int> delta=difference(v,vp);
            // cout<<"v : ";print(v);
            // cout<<"vp : ";print(vp);
            // cout<<"delta : ";print(delta);
            if(mp.count(delta)){
                // cout<<"matdched at : "<<endl;
                int index=mp[delta]+1;
                op.push_back(index);
            }
            mp[v]=i;
        }
        return op;
    }
};