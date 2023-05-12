// problem link : https://codeforces.com/problemset/problem/1401/C
// solution : below code

template<typename T> bool isSorted(vt & v){
    int n=v.size();
    F(i,1,n){
        if(v[i-1]>v[i]) return false;
    }
    return true;
}

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    int mn=*min_element(ALL(v));
    vi unblock;
    F(i,0,n){
        if(v[i]%mn==0) unblock.pb(v[i]);
    }
    SORT(unblock);
    int index=0;
    F(i,0,n){
        if(v[i]%mn==0){
            v[i]=unblock[index];
            index++;
        }
    }
    bool res=isSorted(v);
    YESNO1(res);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
