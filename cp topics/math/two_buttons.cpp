// problem link : https://codeforces.com/problemset/problem/520/B
// solution : below code
#include <iostream>
using namespace std;

int main() {
    int n,m;cin>>n>>m;
    int steps=0;
    while(m>n && m>1){
        if(m%2) m+=1;
        else m/=2;
        steps++;
    }
    steps+=(n-m);
    cout<<steps<<endl;
    return 0;
}
