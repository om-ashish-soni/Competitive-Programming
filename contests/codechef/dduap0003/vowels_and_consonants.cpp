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
bool isVowel(char c){
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
}
void solve(){
    string s;
    cin>>s;
    int cons=0;
    int vowel=0;
    unordered_map<char,int> hash;
    for(auto c:s){
        if(isVowel(c)){
            vowel++;
            hash[c]++;
        }else{
            cons++;
        }
    }
    string vs="aeiou";
    for(int i=0;i<cons;i++){
        char mnc='a';
        int mn=LLONG_MAX;
        for(auto c:vs){
            if(hash.count(c)){
                if(hash[c]<mn){
                    mnc=c;
                    mn=hash[c];
                }
            }
            
        }
        hash[mnc]++;
    }
    char mnc='a';
    int mn=LLONG_MAX;
    for(auto c:vs){
        if(hash.count(c)){
             if(hash[c]<mn){
                mnc=c;
                mn=hash[c];
            }
        }
    }
    cout<<mn<<endl;
}
int32_t main() {
    int t;
    for(cin>>t;t;t--) solve();
    return 0;
}
