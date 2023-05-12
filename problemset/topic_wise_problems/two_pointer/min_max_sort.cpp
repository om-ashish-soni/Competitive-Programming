// problem link : https://codeforces.com/problemset/problem/1792/C
// solution : below code

void solve(int t){
    int n;
    read(n);
    vi v(n);
    readv(v);

    map<int,int> mp;
    F(i,0,n){
        mp[v[i]]=i;
    }
    disjointSet *ds=new disjointSet(n+10);
    F(i,0,n){
        int key=v[i]+1;
        if(mp.count(key) && mp[key]>i){
            ds->prefered_union(v[i],key);
        }
    }
    int mn=LLONG_MAX;
    F(i,0,n){
        int l=v[i];
        int r=ds->findSet(v[i]);
        int before=l-1;
        int after=n-r;
        int sm=before+after-min(before,after);
        mn=min(mn,sm);
    }
    println(mn);
    delete ds;

}
