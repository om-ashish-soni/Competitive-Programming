// problem link : https://codeforces.com/problemset/problem/1713/C
// solution : below code

void perfectperm(vi & v,int l,int r){
    if(l>r) return;
    int sqroot=ceil(sqrt(r));
    int num=sqroot*sqroot;
    int other=num-r;
    perfectperm(v,l,other-1);
    int left=other;
    int right=r;
    while(left<=right){
        v[left]=right;
        v[right]=left;
        left++;
        right--;
    }
}
void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n,-1);
    perfectperm(v,0,n-1);
    printv(v);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
    
