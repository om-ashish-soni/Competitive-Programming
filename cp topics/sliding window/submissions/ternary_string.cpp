#include<bits/stdc++.h>
using namespace std;
int main()
{

    int numberoftestcases = 1;
    cin >> numberoftestcases;
    int t=1;
    while (numberoftestcases--)
    {
        string s;
        cin>>s;
        int n=s.length();
        vector<int> v(4,0);
        int l,r;
        l=r=0;
        int mn=INT_MAX;
        v[int(s[l]-48)]++;
        // cout<<"see this => "<<v[int(s[l]-48)]<<endl;
        while(r<n){
            if(v[1] && v[2] && v[3]){
                mn=min(mn,r-l+1);
                v[int(s[l]-48)]--;
                l++;

            }else{
                r++;
                if(r<n){
                    v[int(s[r]-48)]++;
                }
            }
        }
        if(mn==INT_MAX) mn=0;
        cout<<mn<<endl;
    }
    return 0;
}
