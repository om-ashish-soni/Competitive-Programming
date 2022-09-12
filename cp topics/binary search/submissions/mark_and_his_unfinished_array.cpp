// problem link : https://codeforces.com/problemset/problem/1705/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int c;
    read(c);
    int q;
    read(q);
    string s;
    read(s);
    map<int,int> mp;
    mp[n-1]=n-1;
    int last=n-1;
    F(i,0,c){
        int l,r;
        read(l,r);
        l--;r--;
        int window=r-l+1;
        int new_l=last+1;
        int new_r=new_l+window-1;

        int key=new_r;
        int value=r;
        // auto it=mp.lower_bound(r);
        // int diff=it->first-it->second;
        // value-=diff;        
        mp[key]=value;
        last=new_r;
    }
    // printmap(mp);
    F(i,0,q){
        int index;
        read(index);
        index--;
        // cout<<index<<" => ";
        auto it=mp.lower_bound(index);
        int diff=it->first-it->second;
        // cout<<" diff : "<<diff<<" => "<<endl;
        while(index>=n){
            int old=index;
            auto it=mp.lower_bound(index);
            diff=it->first-it->second;
            index=(index-diff);    
            mp[old]=index;
        }
        
        // cout<<index<<endl;
        println(s[index]);
    }
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
