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
void solve(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int last=0;
    int ans=0;
    for(int i=1;i<n;i++){
        if(arr[i]>=arr[i-1]){
            continue;
        }else{
            int q=i-last;
            last=i;
            ans+=(q*(q+1))/2;
        }
    }
    int q=n-last;
    ans+=(q*(q+1))/2;
    cout<<ans<<endl;
}
int32_t main() {
    int t;
    for(cin>>t;t;t--) solve();
    return 0;
}
