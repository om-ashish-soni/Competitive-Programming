// problem link : https://codeforces.com/problemset/problem/1722/D
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    

    int n;
    read(n);
    string s;
    read(s);
    int sm=0;
    F(i,0,n){
        if(s[i]=='L') sm+=i;
        else sm+=n-i-1;
    }
    vi v(n,0);
    F(i,0,n){
        if(s[i]=='L'){
            int diff=(n-i-1)-i;
            if(diff>0){
                v[i]=diff;
            }
        }else{
            int diff=i-(n-i-1);
            if(diff>0){
                v[i]=diff;
            }
        }
    }
    SORT(v);
    REVERSE(v);
    F(i,1,n){
        v[i]+=v[i-1];
    }
    FEACH(num,v){
        cout<<num+sm<<" ";
    }
    println();

    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
