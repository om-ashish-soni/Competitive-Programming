// problem link : https://codeforces.com/problemset/problem/1446/A
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int w;
    read(w);
    vpii v;
    vi op;
    int sm=0;
    F(i,0,n){
        int num;
        read(num);
        if(num<=w){
            v.pb({num,i+1});    
            sm+=num;
        }
    }
    SORT(v);
    int threshold=(w+1)/2;
    if(sm<threshold){
        return reject();
    }
    int ctr=0;
    int sz=v.size();
    FND(i,sz-1,0){
        if(ctr+v[i].first<=w){
            ctr+=v[i].first;
            op.pb(v[i].second);
            if(ctr>=threshold) break;
        }
    }
    if(ctr<threshold){
        return reject();
    }
    SORT(op);
    cout<<op.size()<<endl;
    printv(op);



    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}
