// problem link : https://codeforces.com/contest/1729/problem/D
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi a(n),b(n);
    readv(a);
    readv(b);
 
    vi pos;
    int zeros=0;
    map<int,int> mp;
    F(i,0,n){
        int diff=a[i]-b[i];
        if(diff==0) zeros++;
        else if(diff>0){
            pos.pb(diff);
        }else{
            mp[abs(diff)]++;
        }
    }
    SORT(pos);
    REVERSE(pos);
    int ctr=0;
    FEACH(num,pos){
        auto it=mp.lower_bound(num);
        if(it != mp.end()){
            // cout<<"taking : "<<num<<" && "<<-it->first<<endl;
            mp[it->first]--;
            if(mp[it->first]<=0) mp.erase(it->first);
            ctr++;
 
        }
    }
    int neg=0;
    FEACH(pr,mp){
        neg+=pr.second;
    }
    int mn=min(neg,zeros);
    ctr+=mn;
    zeros-=mn;
    neg-=mn;
    ctr+=(zeros/2);
    ctr+=(neg/2);
    println(ctr);
 
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
