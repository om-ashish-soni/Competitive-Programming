// problem link : https://leetcode.com/problems/get-equal-substrings-within-budget/description/
// solution : below code

class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int n=s.size();
        vector<int> cost(n,0),pref(n,0);
        for(int i=0;i<n;i++){
            if(i>0) pref[i]=pref[i-1];
            cost[i]=abs(s[i]-t[i]);
            pref[i]+=cost[i];
        }
        int mx=0;
        for(int i=0;i<n;i++){
            int l=0;
            int r=i;
            int window=0;
            while(l<=r){
                bool flag=(l==r);
                int mid=(l+r)/2;
                int delta=pref[i]-pref[mid]+cost[mid];
                if(delta<=maxCost){
                    window=max(window,i-mid+1);
                    r=mid;
                }else{
                    l=mid+1;
                }
                if(flag) break;
            }
            mx=max(mx,window);
        }
        return mx;
    }
};