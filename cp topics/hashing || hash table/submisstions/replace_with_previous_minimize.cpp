// problem link : https://codeforces.com/problemset/problem/1675/E
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n,k;
    read(n,k);
    string s;
    read(s);
    unordered_map<char,char> ump;
    for(char c='a';c<='z';c++){
        ump[c]=c;
    }
    F(i,0,n){
        char c=s[i];
        char ch=c;
        while(ump[ch] == ch && ch>'a' && k>0){
            ch--;
            k--;
        }
        // cout<<c<<" "<<ch<<" "<<k<<endl;
        ch=ump[ch];
        while(c>ch){
            ump[c]=ch;
            c--;
        }
    }
    FEACH(c,s){
        c=ump[c];
    }
    println(s);
}   
