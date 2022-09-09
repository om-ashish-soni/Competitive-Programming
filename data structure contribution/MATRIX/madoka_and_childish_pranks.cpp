// problem link : https://codeforces.com/problemset/problem/1647/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int m;
    read(m);
    vvc mat(n,vc(m));
    readm(mat);//reading matrix
    if(mat[0][0]=='1'){
        return reject();
    }
    vvi queries;
    FND(i,n-1,1){
        FND(j,m-1,0){
            if(mat[i][j]=='1'){
                queries.pb({i-1+1,j+1,i+1,j+1});
            }
        }
    }
    FND(j,m-1,1){
        if(mat[0][j]=='1'){
            queries.pb({0+1,j-1+1,0+1,j+1});
        }
    }
    int q=queries.size();
    println(q);
    FEACH(row,queries){
        printv(row);
    }
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
