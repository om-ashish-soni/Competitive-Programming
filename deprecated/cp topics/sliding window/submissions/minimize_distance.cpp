// problem link : https://codeforces.com/problemset/problem/1585/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int k;
    read(k);
    vi v(n);
    readv(v);
    vi pos,neg;
    int mx=0;
    FEACH(num,v){
        if(num>0) pos.pb(num);
        else if(num<0) neg.pb(-num);
        mx=max(mx,abs(num));
    }
    SORT(pos);
    SORT(neg);
    int ctr=0;
    int pz=pos.size();
    int nz=neg.size();
    for(int i=pz-1;i>=0;){
        int index=i;
        ctr+=2*pos[index];
        i-=k;
    }
    for(int i=nz-1;i>=0;){
        int index=i;
        ctr+=2*neg[index];
        i-=k;
    }
    ctr-=mx;
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
