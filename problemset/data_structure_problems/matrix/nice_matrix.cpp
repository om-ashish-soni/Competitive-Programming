// problem link : 
// solution : below code

template<typename T> double median(vt v){
    double sum=0.0;
    SORT(v);
    int n=v.size();
    if(n%2==1) return v[n/2];
    sum=v[(n-1)/2]+v[(n+1)/2];
    return sum/2.0;
}

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int m;
    read(m);
    vvi mat(n,vi(m));
    readm(mat);
    int cost=0;
    for(int i=0;i<(n+1)/2;i++){
        for(int j=0;j<(m+1)/2;j++){
            vi v(4,0);
            v[0]=mat[i][j];
            v[1]=mat[i][m-1-j];
            v[2]=mat[n-1-i][j];
            v[3]=mat[n-1-i][m-1-j];
            double avg=median(v);
            int first=getdev(v,ceil(avg));
            int second=getdev(v,floor(avg));
            if((n%2==1 && i==n/2) || (m%2==1 && j==m/2)){
                first/=2;
                second/=2;
            }
            
            // cout<<"ceil : "<<ceil(avg)<<" , "<<"floor : "<<floor(avg)<<endl;
            // cout<<i<<","<<j<<" : "<<first<<" vs "<<second<<endl;
            cost+=min(first,second);
        }
    }
    println(cost);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
