#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;


void horspool(string &s,string &p){
    int n=s.size();
    int pz=p.size();
    map<char,int> mp;
    for(auto c:s){
        mp[c]=pz;
    }
    for(int i=0;i<pz-1;i++){
        mp[p[i]]=pz-i-1;
    }
    // for(auto &pr:mp){
    //     cout<<pr.first<<" "<<pr.second<<endl;
    // }
    bool flag=false;
    for(int i=0;i+pz<=n;){
        if(s[i+pz-1]==p[pz-1]){
            int index=pz-2;
            while(index>=0){
                if(s[i+index]!=p[index]){
                    break;
                }
                index--;
            }
            if(index==-1){
                flag=true;
                cout<<"occurrance : "<<i<<endl;
            }
        }
        i+=mp[s[i+pz-1]];
    }
    if(false==flag){
        cout<<"could not find occurrance"<<endl;
    }
}

signed main()
{
    string s;
    string p;
    cin>>s;
    cin>>p;
    cout<<"text : "<<s<<endl;
    cout<<"pattern : "<<p<<endl;
    horspool(s,p);
    return 0;
}

