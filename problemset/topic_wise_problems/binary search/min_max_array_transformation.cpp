// problem link : https://codeforces.com/problemset/problem/1721/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi a(n),b(n);
    readv(a);
    readv(b);

    vb explode(n,false);

    vi mnv(n,0),mxv(n,0);
    int range=n;
    FND(i,n-1,0){
        int index=lower_bound(ALL(b),a[i])-b.begin();
        mnv[i]=b[index]-a[i];
        mxv[i]=b.back()-a[i];
        // int limit=index;
        // explode[limit]=true;
        // // cout<<"limit : "<<limit<<" , index : "<<index<<endl;
        // cout<<"range : "<<range<<" , index : "<<index<<endl;
        range=min(range,index);
        if(range>=i){
            int end=b.size()-1;
            FND(j,end,i){
                b.pop_back();
            }
        }
        
    }
    printv(mnv);
    printv(mxv);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
