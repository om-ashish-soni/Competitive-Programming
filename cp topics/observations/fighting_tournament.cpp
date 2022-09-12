// problem link : https://codeforces.com/problemset/problem/1719/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int q;
    read(q);
    vi v(n);
    readv(v);
    vi score(n,0);
    int winner=0;
    F(i,1,n){
        if(v[i]>v[winner]){
            winner=i;
        }
        score[winner]++;
    }
    F(i,0,q){
        int index,k;
        read(index,k);
        index--;
        int ctr=score[index];
        // cout<<"Index : "<<index<<" : ";
        if(k<n){
            int query=k-max(index,1LL)+1;
            // cout<<query<<" : "<<endl;
            if(query<0) ctr=0;
            else if(query<score[index]){
                ctr=query;
            }
        }
        if(index==winner){
            ctr+=max(0LL,k-n+1);
        }
        println(ctr);
    }
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
