// problem link : https://codeforces.com/problemset/problem/1612/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int x;
    read(x);
    int l=1;
    int r=n;
    int m1=0;
    while(l<=r){
        bool flag=(l==r);
        int mid=(l+r)/2;
        int range=mid*(mid+1)/2;
        if(range<=x+mid-1){
            m1=max(m1,mid);
            l=mid+1;
        }else{
            r=mid;
        }
        if(flag){
            break;
        }
    }
    x-=m1*(m1+1)/2;

    l=1;
    r=n-1;
    int m2=0;
    int overall=(n*(n-1))/2;
    while(l<=r){
        bool flag=(l==r);
        int mid=(l+r)/2;
        int range=overall-mid*(mid-1)/2;
        if(range <= x+mid-1){
            m2=max(m2,n-mid);
            r=mid;
        }else{
            l=mid+1;
        }
        if(flag){
            break;
        }
    }
    
    // cout<<"m1 : "<<m1<<" , m2 : "<<m2<<endl;
    int ctr=m1+m2;
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
 
