// problem link : https://codeforces.com/problemset/problem/1561/C
// solution : below code


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int ctr=0;
    vvi v;
    F(i,0,n){
        int k;
        read(k);
        vi row(k);
        readv(row);
        v.pb(row);
    }
    int score=0;
    vpii caves;
    FEACH(row,v){
        int sz=row.size();
        int defense=0;
        F(i,0,sz){
            defense=max(defense,row[i]-i+1);
        }
        caves.pb({defense,-sz});
    }
    SORT(caves);
    int addon=0;
    int attack=0;
    FEACH(pr,caves){
        attack+=addon;
        int increment=max(0LL,pr.first-attack);
        attack=max(attack,pr.first);
        score+=increment;
        addon=-pr.second;
    }
    println(score);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
