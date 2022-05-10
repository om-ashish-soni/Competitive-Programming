// problem link : https://codeforces.com/problemset/problem/363/B
// solution : below code

void scan(int *arr,int n){
    for(int i=0;i<n;i++){cin>>arr[i];}
}
void solve(){
    int n,k;cin>>n>>k;
    int arr[n];
    scan(arr,n);
    vector<int> pref(n-k+1,0);
    for(int i=n-k;i<n;i++){
        pref[n-k]+=arr[i];
    }
    for(int i=n-k-1;i>=0;i--){
        pref[i]=pref[i+1]+arr[i]-arr[i+k];
    }
    int mn=pref[0];
    int mn_index=0;
    for(int i=1;i<n-k+1;i++){
        if(pref[i]<mn){
            mn=pref[i];
            mn_index=i;
        }
    }
    cout<<mn_index+1<<endl;
}   
