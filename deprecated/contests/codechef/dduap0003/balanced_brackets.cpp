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
void no() {
    cout<<"NO"<<endl;
}
void yes(){
    cout<<"YES"<<endl;
}
void solve(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    int left=count(s.begin(),s.end(),'(');
    int right=count(s.begin(),s.end(),')');
    cout<<min(left,right)*2<<endl;
    return;
}
int32_t main() {
    int t;
    for(cin>>t;t;t--) solve();
    return 0;
}
