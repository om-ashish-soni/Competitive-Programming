// problem link : https://codeforces.com/problemset/problem/1521/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    int mn=LLONG_MAX;
    int min_index=min_element(ALL(v))-v.begin();
    mn=v[min_index];
    vvi steps;
    if(0 != min_index) steps.pb({1,min_index+1,mn,(int)(2e9)});
    int first=mn;
    int second=mn+1;
    F(i,1,n){
        if(i%2) steps.pb({1,i+1,first,second});
        else steps.pb({1,i+1,first,first});
    }
    int sz=steps.size();
    println(sz);
    FEACH(row,steps){
        printv(row);
    }

    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
