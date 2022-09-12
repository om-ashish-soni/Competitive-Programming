// problem link : https://codeforces.com/contest/1729/problem/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    string s;
    read(s);
    n=s.size();
    map<int,vi> mp;
    vector<pair<int, pii>> dp(n,{LLONG_MAX,{0,-1}});
    F(i,0,n){
        mp[s[i]].pb(i);
    }
    
    
    vi v;
    map<char,bool> visited;
 
    char mn=s[0];
    char mx=s[n-1];
    if(mn>mx){
        swap(mn,mx);
        // if(v.size()>1) reverse(v.begin()+1,v.end());
    }
    v.pb(1);
    FEACH(pr,mp){
        char c=pr.first;
        if(mn<=c && c<=mx && visited.count(c)==0){
            visited[c]=true;
            vi & row=mp[c];
            FEACH(num,row){
                if(num+1 != 1 && num+1 != n) 
                v.pb(num+1);
            }
        }
    }
    if(v.size()>1 && s[0]>s[n-1]){
        reverse(v.begin()+1,v.end());
    }
    v.pb(n);
    int cost=mx-mn;
    int jumps=v.size();
    println(cost,jumps);
    printv(v);
 
 
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
