#include <bits/stdc++.h>
#define int long long 
#define ll long long
#define endl "\n"

/*

 ___________________________________________________________
| AUTHOR  : Om Ashish Soni                                  |
| code    : C++14                                           |
| IDE     : Sublime txt                                     | 
|___________________________________________________________|

*/
using namespace std;
unordered_map<int,int> m11,m10,m00,m01;
int maxSum(vector<int>& v,int n,int index,bool isTake,bool isTakeNext){
    // taking index
    if(index>=n) return 0;
    if(isTake && isTakeNext){
        //take both
        if(m11.count(index)) return m11[index];
        int mx=maxSum(v,n,index+2,false,true);
        mx=max(mx,maxSum(v,n,index+2,false,false));
        mx+=v[index];
        if(index+1<n){
            mx+=v[index+1];
        }
        m11[index]=mx;
        return mx;
    }
    if(isTake){
        // take this, but not the next
        if(m10.count(index)) return m10[index];
        int mx=maxSum(v,n,index+1,false,true);
        mx=max(mx,maxSum(v,n,index+1,false,false));
        mx+=v[index];
        m10[index]=mx;
        return mx;
    }
    if(m00.count(index)) return m00[index];
    int mx=maxSum(v,n,index+1,true,false);
    mx=max(mx,maxSum(v,n,index+1,true,true));
    mx=max(mx,maxSum(v,n,index+1,false,false));
    m00[index]=mx;
    return mx;
    
}
void solve(){
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){cin>>v[i];}
    int mx=0;
    m00.clear();
    m10.clear();
    m11.clear();
    mx=maxSum(v,n,0,false,false);
    mx=maxSum(v,n,0,false,true);
    mx=max(mx,maxSum(v,n,0,true,false));
    mx=max(mx,maxSum(v,n,0,true,true));
    cout<<mx<<endl;
}
int32_t main() {
    int t;
    // for(cin>>t;t;t--) 
    solve();
    return 0;
}
