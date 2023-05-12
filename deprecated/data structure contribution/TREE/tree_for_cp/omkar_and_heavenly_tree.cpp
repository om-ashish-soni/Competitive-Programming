// problem link : https://codeforces.com/problemset/problem/1583/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int m;
    read(m);
    int root=-1;
    vi visited(n+1,false);
    F(i,0,m){
        int x,y,z;
        read(x,y);
        read(z);
        visited[y]=true;
    }
    F(i,1,n+1){
        if(visited[i]==false){
            root=i;
            break;
        }
    }
    F(i,1,n+1){
        if(root != i){
            println(root,i);
        }
    }
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
