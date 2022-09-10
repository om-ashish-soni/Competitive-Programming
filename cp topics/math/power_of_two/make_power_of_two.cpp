// problem link : https://codeforces.com/problemset/problem/1560/D
// solution : below code

string intToString(int n){
    ostringstream ostr;
    ostr<<n;
    return ostr.str();
}

void solve(int t){
    //shree ganeshay namah  
    string s;
    read(s);
    int n=s.size();
    int limit=1e18+10;
    int num=1;
    vs pws;
    while(num<limit){
        pws.pb(intToString(num));
        num<<=1;
    }
    int mn=LLONG_MAX;
    FEACH(key,pws){
        int sz=key.size();
        int found=-1;
        bool isDone=false;
        F(i,0,sz){
            found=s.find(key[i],found+1);
            if(found>=0 && found<n){
                ;
            }else{
                isDone=true;
                int rem=sz-i;
                int done=i;
                int cost=n-done+rem;
                mn=min(mn,cost);
                break;
            }
        }
        if(isDone==false){
            int done=sz;
            int rem=0;
            int cost=n-done+rem;
            mn=min(mn,cost);
        }
    }
    println(mn);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
    
