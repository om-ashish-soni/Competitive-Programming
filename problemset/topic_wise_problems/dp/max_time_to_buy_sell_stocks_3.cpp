// problem link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
// solution : below code

            
class Solution {
public:
    vector<int> refine(vector<int> v){
        vector<int> v1;
        for(auto num:v){
            int sz=v1.size();
            if(sz>=2 && v1.back()>=num){
                if(v1[sz-2]>=v1[sz-1]){
                    v1.pop_back();
                }
                v1.push_back(num);
            }else{
                v1.push_back(num);
            }
        }
        // for(auto num:v1) cout<<num<<" ";cout<<endl;
        return v1;
    }
    int maxProfit(vector<int>& prices) {
        prices=refine(prices);
        int n=prices.size();
        vector<int> pref(n,0);
        vector<int> suff(n,0);
        int mx=0;
        int mn1=prices[0];
        for(int i=1;i<n;i++){
            pref[i]=max(pref[i-1],prices[i]-mn1);
            mn1=min(mn1,prices[i]);
        }
        int mx1=prices[n-1];
        for(int i=n-2;i>=0;i--){
            suff[i]=max(mx1-prices[i],suff[i+1]);
            mx1=max(mx1,prices[i]);
        }
        for(int i=0;i<n-1;i++){
            // cout<<"i : "<<i<<" = "<<pref[i]<<" + "<<suff[i+1]<<endl;
            int delta=pref[i]+suff[i+1];
            mx=max(mx,delta);
        }
        for(int i=0;i<n;i++){
            mx=max(mx,pref[i]);
            mx=max(mx,suff[i]);
        }
        return mx;
    }
};