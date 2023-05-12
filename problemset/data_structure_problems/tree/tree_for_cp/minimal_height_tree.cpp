// problem link : https://codeforces.com/problemset/problem/1437/D
// solution : below code

#define map unordered_map
void solve(int t){
    int n;
    read(n);
    vi v(n);
    readv(v);
    queue<int> stk;
    vi height(n+1,-1);
    int anc=1;
    height[1]=0;
    for(int i=1;i<n;){
        // cout<<"parent : "<<anc<<" , node : "<<v[i]<<endl;
        height[v[i]]=height[anc]+1;
        stk.push(v[i]);
        i++;
        for(;i<n;i++){
            if(v[i-1]>v[i])  {
                break;
            }
            // cout<<"parent : "<<anc<<" , node : "<<v[i]<<endl;
            height[v[i]]=height[anc]+1;
            stk.push(v[i]);
        }
        anc=stk.front();
        stk.pop();
    }
    // printv(v);
    // printv(height);
    int mx=*max_element(ALL(height));
    println(mx);
}

signed main(){
    FASTIO;
    BOOLALPHA;
    int t=1;;
    read(t);//isTakeTestCase
    F(i,1,t+1){
        solve(i);
    }
    printTime();
    return 0;
}   
