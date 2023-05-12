// problem link : https://codeforces.com/problemset/problem/1704/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int m;
    read(m);
    vi v(m);
    readv(v);
    priority_queue<pair<int, pii>> pq;
    SORT(v);
    F(i,1,m){
        pq.push({v[i]-v[i-1]-1,{v[i-1],v[i]}});
    }
    pq.push({n-v[m-1]+v[0]-1,{v[m-1],n+v[0]}});
    int tm=0;
    int saved=0;
    while(pq.size()>0){
        pair<int, pii> top=pq.top();pq.pop();
        pii pr=top.second;
        // cout<<"tm : "<<tm<<", left : "<<pr.first<<" , right : "<<pr.second<<endl;
        int left=pr.first+1+tm;
        if(left<pr.second-tm){
            saved++;
            tm++;
            int right=pr.second-1-tm;
            if(left<right){
                saved++;
                tm++;
                int diff=right-left-1;
                if(diff>0) saved+=diff;
            }
        }
    }
    int ctr=n-saved;
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
