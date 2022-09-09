// problem link : https://codeforces.com/problemset/problem/1617/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    vb visited(n+1,false);
    FND(i,n-1,0){
        int num=v[i];
        if(num<=n && visited[num]==false){
            visited[num]=true;
            swap(v[i],v[v.size()-1]);
            v.pop_back();
        }
    }
    vi residue;
    F(i,1,n+1){
        if(visited[i]==false) residue.pb(i);
    }
    SORT(v);
    int sz=residue.size();
    int ctr=0;
    F(i,0,sz){
        int limit=(v[i]+1)/2 - 1;
        if(residue[i]>limit){
            return reject();
        }
        ctr++;
    }
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
