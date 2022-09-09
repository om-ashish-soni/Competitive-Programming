// problem link : https://codeforces.com/problemset/problem/1669/E
// solution : below code



void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vs v(n);
    readv(v);
    map<string,int> mp;
    int ctr=0;
    FEACH(key,v){
        mp[key]++;
    }
    FEACH(key,v){
        for(int i=0;i<2;i++){
            char original=key[i];
            for(char c='a';c<='z';c++){
                if(c != original){
                    key[i]=c;
                    ctr+=mp[key];
                }
            }
            key[i]=original;
        }
    }
    ctr>>=1;
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
