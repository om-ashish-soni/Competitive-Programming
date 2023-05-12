// Problem link : https://www.codechef.com/submit/IRSTXOR
// Problem type : Greedy
#include <bits/stdc++.h>
#define int long long
using namespace std;
void printV(std::vector<int> &v){
    for(auto num:v){
        cout<<num<<" ";
    }
    cout<<endl;
    return;
}
void convert(int n,std::vector<int> &v){
    while(n>0){
        v.push_back(n&1);
        n>>=1;
    }
}
int32_t main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> binN;
        convert(n,binN);
        // vector<int> big(binN.size());
        // vector<int> small(binN.size());
        int i=0;
        int bigNum=0,smallNum=0,mul=1;
        for(i=0;i<binN.size()-1;i++){
            if(binN[i]==0){
                // big[i]=1;
                bigNum+=mul;
            }
            // small[i]=1;
            smallNum+=mul;
            mul*=2;
        }
        // small[i]=0;
        // big[i]=binN[i];
        bigNum+=mul*binN[i];
        // cout<<bigNum<<" "<<smallNum<<endl;
        cout<<bigNum*smallNum<<endl;
    }
    return 0;
}
