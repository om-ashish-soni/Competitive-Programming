// problem link : https://leetcode.com/problems/count-number-of-teams/
// solution : below code

class Solution {
public:
    int numTeams(vector<int>& rating) {
        vector<int>& arr=rating;
        int n=rating.size();
        vector<pair<int,int>> dp(n);
        int ctr=0;
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(arr[i]<arr[j]){
                    ctr+=dp[j].first;
                    dp[i].first++;
                }if(arr[i]>arr[j]){
                    ctr+=dp[j].second;
                    dp[i].second++;
                }
            }
        }
        return ctr;
    }
};
