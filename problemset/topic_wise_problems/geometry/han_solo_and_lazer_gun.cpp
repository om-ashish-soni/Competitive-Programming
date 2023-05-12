// problem link : https://codeforces.com/problemset/problem/514/B
// solution : below code


void solve(int t){
    int n;
    cin>>n;
    int a,b;
    cin>>a>>b;
    vector<pair<int,int>> points;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        bool linear=false;
        x=(x-a);
        y=(y-b);
        for(auto & pr:points){
            
            if(pr.first*y == pr.second*x){
                linear=true;
                break;
            }
        }
        if(linear==false){
            points.push_back({x,y});
        }
    }
    int ctr=points.size();
    cout<<ctr<<endl;
}
