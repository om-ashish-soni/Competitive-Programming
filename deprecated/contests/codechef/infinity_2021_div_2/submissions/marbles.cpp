// Problem link : https://www.codechef.com/INFI21B/problems/MARBLE
// Problem type : simple, strings
#include <bits/stdc++.h>
#define int long long int
#define endl "\n"
#define rep(i,n,k)       for(ll i=0;i<n;i+=k)
#define rrep(i,n,k)      for(ll i=n;i>=0;i-=k)
#define rep1(i,n,k)      for(ll i=1;i<n;i+=k)
#define vi               vector<int>
#define vl               vector<ll>
#define vs               vector<string>
#define vvi              vector<vi>
#define fast             ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pb               push_back
#define mp               make_pair
#define ff                first
#define se                second
#define maxn              1e6+3
#define inf               1e18
#define modulo               1e9+7
#define pi               3.1415926535897932384626433832795
#define testcase(t)     long long t;cin>>t;while(t--)
#define mem(dp,i)        memset(dp,i,sizeof(dp))
#define all(x)           (x).begin(), (x).end()
#define dbg(x)           cout<<x<<" = "<<x<<endl
/*

 ___________________________________________________________
| AUTHOR  : Om Ashish Soni                                  |
| code    : C++14                                           |
| IDE     : Online IDE                                      | 
|___________________________________________________________|

*/
using namespace std;
class class_name
{
    int n,count,*arr;
    string s;
    public:
    bool isVowel(char c){
        return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
    }

    bool isCons(char c){
        return !isVowel(c);
    }
    char maxVowel(vector<int>&v){

        int mx=max(v['a'],max(v['e'],max(v['i'],max(v['o'],v['u']))));
        if(mx==v['a']) return 'a';
        if(mx==v['e']) return 'e';
        if(mx==v['i']) return 'i';
        if(mx==v['o']) return 'o';
        return 'u';
    }
    char maxCons(vector<int>&v){
        char c='b';
        int mx=v['b'];
        for(int i=99;i<123;i++){
            if(isCons(i)){
                // cout<<char(i)<<" is cons"<<endl;
                if(v[i]>mx){
                    mx=v[i];
                    c=i;
                }
            }
        }
        return c;
    } 
    int compute(string s,string p,vector<int>&v,char c){
        int steps=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='?') s[i]=c;
            if(p[i]=='?') p[i]=c;   
            if(s[i]!=p[i]){
                bool sVowel=isVowel(s[i]);
                bool pVowel=isVowel(p[i]);
                // cout<<s[i]<<" "<<p[i]<<" "<<steps<<endl;
                if(sVowel==pVowel) steps+=2;
                else steps++;
                
            }
        }
        return steps;
    }
    class_name()
    {
        string s,p;
        int n;
        cin>>n;
        cin>>s>>p;
        vector<int> v(130,0);
        int vowelCount,consCount;
        vowelCount=0;
        consCount=0;
        int steps=0;
        string newS,newP;
        for(int i=0;i<s.size();i++){
            bool sVowel=isVowel(s[i]);
            bool pVowel=isVowel(p[i]);
            if(s[i]==p[i]);
            else if(s[i]=='?' && p[i]=='?') s[i]=p[i]='a';
            else if(s[i]=='?'){
                v[p[i]]++;
                if(pVowel) vowelCount++;else consCount++;
            }else if(p[i]=='?'){
                v[s[i]]++;
                if(sVowel) vowelCount++;else consCount++;
            }else if(sVowel == pVowel){
                // cout<<s[i]<<" "<<p[i]<<" "<<steps<<endl;
                steps+=2;
                s[i]=p[i];
            }else {
                // cout<<s[i]<<" "<<p[i]<<" "<<steps<<endl;
                steps++;
                s[i]=p[i];
            }
        }
        int mx=max_element(v.begin(),v.end())-v.begin();
        char mxVowel,mxCons;
        mxVowel=maxVowel(v);
        mxCons=maxCons(v);
        char c=mx;
        if(v[mxVowel]==v[mxCons] || max(v[mxVowel],v[mxCons])==1){
            c=mxVowel;
        }else{
            if(v[mxVowel]>v[mxCons]){
                c=mxCons;
            }else{
                c=mxVowel;
            }
        }
        // cout<<" mx C : "<<mxCons<<" ; "<<" mx V : "<<mxVowel<<endl;
        int temp=min(compute(s,p,v,mxCons),compute(s,p,v,mxVowel));
        steps+=temp;
        // cout<<" tmep : "<<temp<<endl;
        cout<<steps<<endl;
        // arr=new int[n];
    }
    ~class_name(){
        // delete[] arr;
    }
};
int32_t main() {
    int t;
    cin>>t;
    while(t--) class_name object_name;
    return 0;
}
