// problem link : https://leetcode.com/problems/car-pooling/description/
// solution : below code

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        const int len=1e3+10;
        vector<int> pref(len,0);
        int n=trips.size();
        for(int i=0;i<n;i++){
            vector<int> & group=trips[i];
            int ctr=group[0];
            int start=group[1];
            int end=group[2];
            pref[start]+=ctr;
            pref[end]-=ctr;
        }
        if(pref[0]>capacity) return false;
        for(int i=1;i<len;i++){
            pref[i]+=pref[i-1];
            if(pref[i]>capacity) return false;
        }
        return true;
        
    }
};