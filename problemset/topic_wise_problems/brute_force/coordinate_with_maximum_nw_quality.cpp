// problem link : https://leetcode.com/problems/coordinate-with-maximum-network-quality/description/
// solution : below code

class Solution {
public:
    int distance(int a,int b,int c,int d){
        int dx=c-a;
        int dy=d-b;
        return (dx*dx + dy*dy);
    }
    vector<int> bestCoordinate(vector<vector<int>>& towers, int r) {
        vector<int> v_mn={INT_MAX,INT_MAX};
        vector<int> v_mx={0,0};
        for(auto & tower:towers){
            for(int i=0;i<2;i++){
                v_mn[i]=min(tower[i],v_mn[i]);
                v_mx[i]=max(tower[i],v_mx[i]);
            }
        }
        pair<int,int> point={0,0};
        int mx=0;
        for(int x=v_mn[0];x<=v_mx[0];x++){
            for(int y=v_mn[1];y<=v_mx[1];y++){
                int quality=0;
                for(auto & tower:towers){
                    int dx=tower[0];
                    int dy=tower[1];
                    int dist=distance(x,y,dx,dy);
                    // cout<<x<<" , "<<y<<" vs "<<dx<<" , "<<dy<<" :dist: "<<dist<<endl;
                    if(dist<=r*r) quality+=(1.0*tower[2])/(1+sqrt(dist));
                }
                if(quality>mx){
                    mx=quality;
                    point={x,y};
                }else if(quality==mx){
                    if(point.first>x || point.first==x && point.second>y){
                        point={x,y};
                    }
                }
            }
        }
        return {point.first,point.second};
    }
};