// problem link : https://codeforces.com/problemset/problem/1558/A
// solution : below code


void playMatch(int first,int second,int a,int b,map<int,bool>& mp){
    int limit=min(a,first);
    F(i,0,limit+1){
        int rest=a-i;
        if(rest<=second){
            int ascore=i;
            int bscore=second-rest;
            int score=ascore+bscore;
            // cout<<ascore<<" vs "<<bscore<<" a,b : "<<a<<","<<b<<" : "<<score<<endl;
            mp[score]=true;
        }
    }
}
void solve(int t){
    //shree ganeshay namah  
    int a,b;
    read(a,b);
    int n=(a+b);
    int first=(n+1)/2;
    int second=n-first;
    map<int,bool> mp;

    playMatch(first,second,a,b,mp);
    swap(first,second);
    playMatch(first,second,a,b,mp);

    vi v;
    FEACH(pr,mp) v.pb(pr.first);
    int sz=v.size();
    cout<<sz<<endl;
    printv(v);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
