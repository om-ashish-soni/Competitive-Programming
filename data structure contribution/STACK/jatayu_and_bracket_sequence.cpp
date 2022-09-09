// problem link : https://codeforces.com/problemset/problem/1726/C
// solution : below code

        
        
int levelorder(string &s , map<int,int> & mp,int l,int r){
    if(l>=r) return 0;
    int ctr=1;
    for(int i=l;i<=r;){
        int start=i;
        int end=mp[i];
        // cout<<"start : "<<start<<" , end : "<<end<<endl;
        ctr+=levelorder(s,mp,start+1,end-1);
        i=end+1;
    }
    return ctr;
}
void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    n=n*2;
    string s;
    read(s);
    int ctr=0;
    int mx=0;
    stack<int> stk;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        if(s[i]=='('){
            stk.push(i);
        }else{
            int top=stk.top();
            mp[top]=i;
            stk.pop();
        }
    }
    ctr=levelorder(s,mp,0,n-1);
    println(ctr);
    // kick(t);
    
    // write your answer here
    // println(pref);
    
    //complete your answer here
    // println();
}   
