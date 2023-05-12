// problem link : https://codeforces.com/problemset/problem/158/B

// solution : below code

void solve(int t){
    int n;
    read(n);
    vi v(n);
    readv(v);
    vi mp(5,0);
    FEACH(num,v){
        mp[num]++;
    }   
    int ctr=0;
    ctr+=mp[4];
    int cmp13=min(mp[1],mp[3]);
    mp[1]-=cmp13;
    mp[3]-=cmp13;
    ctr+=cmp13;
    int cmp33=mp[3];
    mp[3]-=cmp33;
    ctr+=cmp33;
    int cmp12=min((mp[1]+1)/2,mp[2]);
    mp[1]-=2*cmp12;
    mp[2]-=cmp12;
    ctr+=cmp12;
    int cmp22=(mp[2]+1)/2;
    mp[2]-=2*cmp22;
    ctr+=cmp22;
    int cmp11=(mp[1]+3)/4;
    mp[1]-=4*cmp11;
    ctr+=cmp11;
    println(ctr);
}




