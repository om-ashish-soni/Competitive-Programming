// problem link : https://leetcode.com/contest/weekly-contest-294/problems/minimum-lines-to-represent-a-line-chart/
// solution : below code

#define pii pair<int,int>
#define vpii vector<pii>
#define vd vector<double>
#define pb push_back
#define ll long long
class Solution {
public:
    double slope(double x1,double y1,double x2,double y2){
        return (double)(y2-y1)/(double)(x2-x1)*(1.0);
    }
    bool doit(ll sy,ll cy,ll sx,ll cx){
        if(cx==0){
            if(sx==0){
                return true;
            }
            return false;
        }
        return sy*cx==sx*cy;
    }
    int minimumLines(vector<vector<int>>& stockPrices) {
        int n=stockPrices.size();
        vpii v(n);
        for(int i=0;i<n;i++) v[i]={stockPrices[i][0],stockPrices[i][1]};
        sort(begin(v),end(v));
        
        vpii sl;
        for(int i=1;i<n;i++){
            int yd=v[i].second-v[i-1].second;
            int xd=v[i].first-v[i-1].first;
            if(sl.size()==0) sl.pb({yd,xd});
            else if(doit(sl.back().first,yd,sl.back().second,xd)){
                ;
            }else{
                sl.pb({yd,xd});
            }
        }
        
        return (int)(sl.size());
    }
};
