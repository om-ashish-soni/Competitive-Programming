// problem link : https://codeforces.com/problemset/problem/1644/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
        

    int n;
    read(n);
    int k;
    read(k);
    vi v(n);
    readv(v);
    vi vmx(n+1,0);
    vi pref(n,0);
    pref[0]=v[0];
    F(i,1,n){
        pref[i]=pref[i-1]+v[i];
    }
    vmx[0]=0;

    // println(vmx[0]);
    // return;

    F(i,1,n+1){
        int mxi=-1;
        int mx=LLONG_MIN;
        F(j,0,n-i+1){
            int curr=pref[j+i-1]-pref[j]+v[j];
            if(curr>mx){
                mx=curr;
                mxi=j;
            }
        }
        vmx[i]=mx;
    }
    // printv(vmx);
    vi op(n+1,0LL);
    F(i,0,n+1){
        int curr=0;
        F(j,i,n+1){
            curr=max(curr,vmx[j]+i*k);
        }
        op[i]=curr;
        if(i>0) op[i]=max(op[i-1],op[i]);
    }
    printv(op);
    
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
