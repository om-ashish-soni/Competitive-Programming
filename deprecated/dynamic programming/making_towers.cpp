// problem link : https://codeforces.com/problemset/problem/1706/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
        

    int n;
    read(n);
    vi v(n);
    readv(v);
    vi dp(n+1,0);
    vi curr(n+1,0);
    map<int,vi> mp;
    F(i,0,n){
        mp[v[i]].pb(i);
    }   
    FEACH(pr,mp){
        int d_odd=0;
        int d_even=0;
        vi & row=pr.second;
        int num=pr.first;
        curr[num]=1;
        FEACH(index,row){
            if(index%2==0){
                curr[num]=d_odd+1;
                d_even=max(d_even,curr[num]);
            }else{
                curr[num]=d_even+1;
                d_odd=max(d_odd,curr[num]);
            }
            // if(index-1>=0){
            //     if(v[index-1]==num){
            //         curr[num]++;
            //     }else if(index-3>=0){
            //         if(v[index-3]==num){
            //             curr[num]++;
            //         }
            //     }else{
            //         dp[num]=max(dp[num],curr[num]);
            //         curr[num]=1;
            //     }
            // }
        }
        dp[num]=max(dp[num],curr[num]);
    }
    F(i,1,n+1){
        print(dp[i]);
    }
    println();

    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
