// problem link : https://codeforces.com/problemset/problem/1372/C
// solution : below code

void solve(int t){
    int n;
    read(n);
    vi v(n);
    readv(v);
    vb should(n,true);
    F(i,0,n){
        should[i]=(v[i]==i+1);
    }
    disjointSet *ds=new disjointSet(n);
    F(i,1,n){
        if(should[i]==should[i-1]){
            ds->prefered_union(i,i-1);
        }
    }
    set<int> roots;
    F(i,0,n){
        int root=ds->findSet(i);
        if(should[root]==false){
            roots.insert(root);
        }
    }
    int inv=roots.size();
    if(inv<2){
        println(inv);
    }else{
        cout<<2<<endl;
    }
    delete ds;
}
