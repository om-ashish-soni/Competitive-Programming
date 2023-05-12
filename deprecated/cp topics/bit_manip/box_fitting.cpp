// problem link : https://codeforces.com/problemset/problem/1498/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int w;
    read(w);
    vi v(n);
    readv(v);
    map<int,int> mp;
    FEACH(num,v){
        int key=log2(num);
        mp[key]++;
    }
    bitset<32> bs(w);
    int ctr=1;
    int h=0;
    while(ctr>0){
        ctr=0;
        int rollover=0;
        FND(k,31,0){
            
            int cut=bs[k];
            cut+=rollover;
            int used=0;
            if(mp.count(k)){
                used=min(cut,mp[k]);
                mp[k]-=cut;
                if(mp[k]<=0) mp.erase(k);
                ctr++;
            }
            rollover=(cut-used)*2;
            // cout<<"k : "<<k<<" , cut : "<<cut<<" , used : "<<used<<endl;
                
        }
        // cout<<"ctr"<<" : "<<ctr<<endl;
        if(ctr>0) h++;
    }
    println(h);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
