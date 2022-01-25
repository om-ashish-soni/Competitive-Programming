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
static int arr[(int)(1e6+1)];
int mod=1e9+9;
void solve(){
    int n;
    cin>>n;
    cout<<arr[n]%mod<<endl;
}
int32_t main() {
    arr[0]=1;
    int N=(int)(1e6);
    for(int i=0;i<=N;i++){
        if(arr[i]==0) continue;
        if(i+2<=N){
            arr[i+2]=(arr[i+2]+arr[i])%mod;
            if(i+3<=N) arr[i+3]=(arr[i+3]+arr[i])%mod;
        }
    }
    int t;
    for(cin>>t;t;t--) solve();
    return 0;
}
