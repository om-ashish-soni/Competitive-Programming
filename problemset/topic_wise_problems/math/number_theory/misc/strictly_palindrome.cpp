// problem link : https://leetcode.com/problems/strictly-palindromic-number/description/
// solution : below code

class Solution {
public:
    bool ispal(vector<int> v){
        int n=v.size();
        for(int i=0;i<n/2;i++){
            if(v[i] != v[n-i-1]) return false;
        }
        return true;
    }
    vector<int> basify(int n,int base){
        vector<int> v;
        while(n>0){
            v.push_back(n%base);
            n/=base;
        }
        return v;
    }
    bool isStrictlyPalindromic(int n) {
        for(int i=2;i<=n-2;i++){
            if(ispal(basify(n,i))==false) return false;
        }
        return true;
    }
};