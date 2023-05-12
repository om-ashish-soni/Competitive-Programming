// problem link : https://codeforces.com/problemset/problem/1594/C
// solution : below code


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    char c;
    read(c);
    string s;
    read(s);
    if(isAllSame(s,c)){
        cout<<0<<endl;
        return;
    }
    F(i,1,n+1){
        bool isChance=true;
        for(int j=i;j<=n;j+=i){
            if(s[j-1]!=c){
                isChance=false;
                break;
            }
        }
        if(isChance){
            cout<<1<<endl;
            cout<<i<<endl;
            return;
        }
    }
    cout<<2<<endl;
    int first=n;
    int second=n-1;
    println(first,second);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
    
