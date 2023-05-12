// problem link : https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/
// solution : below code

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n=points.size();
        vector<int> numbers;
        vector<pair<int,int>> v(n);
        for(auto & row:points){
            for(auto elem:row) numbers.push_back(elem);
        }
        for(int i=0;i<n;i++){
            v[i].first=points[i][0];
            v[i].second=points[i][1];
        }
        sort(v.begin(),v.end());
        for(int i=n-2;i>=0;i--){
            v[i].second=min(v[i].second,v[i+1].second);
        }
        vector<int> dp(n+1,INT_MAX);
        dp[n]=0;
        for(int i=n-1;i>=0;i--){
            int l=i+1;
            int r=n-1;
            int reach=i;
            while(l<=r){
                bool flag=(l==r);
                int mid=(l+r)/2;
                int index=mid;
                if(v[index].first>v[i].second){
                    r=mid;
                }else if(v[index].second>=v[i].second){
                    reach=max(reach,index);
                    l=mid+1;
                }else{
                    r=mid;
                }
                if(flag) break;
            }
            dp[i]=dp[reach+1]+1;
        }
        return dp[0];
    }
};