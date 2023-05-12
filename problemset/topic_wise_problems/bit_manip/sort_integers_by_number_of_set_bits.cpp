// problem link : https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/description/
// solution : below code

class Solution {
public:
    int bits(int n){
        int ctr=0;
        while(n>0){
            ctr+=(n&1);
            n>>=1;
        }
        return ctr;
    }
    vector<int> sortByBits(vector<int>& arr) {
        int n=arr.size();
        vector<pair<int,int>> v;
        for(int i=0;i<n;i++){
            v.push_back({bits(arr[i]),arr[i]});
        }
        sort(v.begin(),v.end());
        for(int i=0;i<n;i++){
            arr[i]=v[i].second;
        }
        return arr;
    }
};