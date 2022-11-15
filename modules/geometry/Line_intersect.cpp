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
class LineIntersect{
public:
    
    
    
    static bool isIntersect(pii & p1,pii & p2,pii & p3, pii & p4){
        int d1,d2,d3,d4;
        d1=Line::direction(p3,p4,p1);
        d2=Line::direction(p3,p4,p2);
        d3=Line::direction(p1,p2,p3);
        d4=Line::direction(p1,p2,p4);
        if(d1*d2<0 && d3*d4<0){
            return true;
        }else if(d1==0 && Line::onSegment(p3,p4,p1)){
            return true;
        }else if(d2==0 && Line::onSegment(p3,p4,p2)){
            return true;
        }else if(d3==0 && Line::onSegment(p1,p2,p3)){
            return true;
        }else if(d4==0 && Line::onSegment(p1,p2,p4)){
            return true;
        }
        return false;
    }    
};

signed main()
{
    pii p1,p2,p3,p4;
    p1={1,1};
    p2={3,3};
    p3={5,5};
    p4={8,8};
    bool result=LineIntersect::isIntersect(p1,p2,p3,p4);
    cout<<boolalpha;
    cout<<result<<endl;
    return 0;
}

