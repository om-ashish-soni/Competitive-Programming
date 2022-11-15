#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;

class Point{
public:
    static void printPoint(pii & p1){
        cout<<"("<<p1.first<<","<<p1.second<<")"<<endl;
    }
    static pii subtract(pii & p1,pii & p2){
        return {p1.first-p2.first,p1.second-p2.second};
    }
};
class Line{
public:
    static int direction(pii & p1,pii & p2,pii & p3){
        pii p1p2=Point::subtract(p2,p1);
        pii p1p3=Point::subtract(p3,p1);
        int d=p1p3.first*p1p2.second - p1p3.second*p1p2.first;
        return d;
    }
    static bool onSegment(pii & p1,pii & p2,pii & p3){
        return isInrange(p1.first,p2.first,p3.first) && isInrange(p1.second,p2.second,p3.second);
    }
    static bool isInrange(int a,int b,int c){
        return min(a,b)<=c && c<=max(a,b);
    }
};

class ConvexHull{
public:
    static void solveJarvis(vector<pii> & points,vector<pii> & hull){
        int n=points.size();
        if(n<3) return ;
        int l=0;
        pii mn={LLONG_MAX,LLONG_MAX};
        for(int i=0;i<n;i++){
            if(points[i]<mn){
                mn=points[i];
                l=i;
            }
        }
        int p=l,q=0;
        do{
            hull.push_back(points[p]);
            q=(p+1)%n;
            for(int i=0;i<n;i++){
                if(Line::direction(points[p],points[i],points[q])<0){
                    q=i;
                }
            }
            p=q;
        }while(p != l);

    }
};
signed main()
{
    vector<pii> hull;
    vector<pii> points={
        {0,3},
        {2,2},
        {1,1},
        {2,1},
        {3,0},
        {0,0},
        {3,3}
    };
    ConvexHull::solveJarvis(points,hull);
    for(auto & pr:hull){
        cout<<pr.first<<" , "<<pr.second<<endl;
    }
    return 0;
}

