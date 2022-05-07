#include <bits/stdc++.h>
#define int long
using namespace std;
void print(char c,int freq){
    for(int i=0;i<freq;i++){
        cout<<c;
    }
}
int32_t main() {
    int t;
    cin>>t;
    while(t--){
        string s,t;
        cin>>s>>t;
        int a,b,c;
        a=b=c=0;
        string other;
        for(auto ch:s){
            if(ch=='a' ) a++;
            else if(ch=='b') b++;
            else if(ch=='c') c++;
            else other+=ch;
        }
        sort(other.begin(),other.end());   
        if(a==0 || b==0 || c==0){
            print('a',a);
            print('b',b);
            print('c',c);
        }     
        else if(t=="abc"){
            print('a',a);
            print('c',c);
            print('b',b);
        }else{
            print('a',a);
            print('b',b);
            print('c',c);
        }
        cout<<other<<endl;
    }
    // your code goes here
    return 0;
}
