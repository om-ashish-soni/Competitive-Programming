// problem link : https://leetcode.com/problems/two-best-non-overlapping-events/description/
// solution : below code

class Solution {
public:
    #define map unordered_map
    int maxTwoEvents(vector<vector<int>>& events) {
        set<int> st;
        for(auto & event:events){
            int l=event[0];
            int r=event[1];
            st.insert(l);
            st.insert(r);
        }
        map<int,int> mp;
        mp.reserve(st.size()+10);
        int key=0;
        for(auto num:st){
            mp[num]=key;
            key++;
        }
        vector<int> v(key+10,0);
        for(auto event:events){
            int l=event[0];
            int r=event[1];
            int value=event[2];
            l=mp[l];
            r=mp[r];
            v[l]=max(v[l],value);
        }
        int sz=v.size();
        for(int i=sz-2;i>=0;i--){
            v[i]=max(v[i],v[i+1]);
        }
        int mx=0;
        for(auto event:events){
            int l=event[0];
            int r=event[1];
            int value=event[2];
            l=mp[l];
            r=mp[r];
            mx=max(mx,value+v[r+1]);
        }
        return mx;
    }
};