// problem link : https://codeforces.com/problemset/problem/1720/C
// solution : below code


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int m;
    read(m);
    vvc mat(n,vc(m));
    readm(mat);
    bool singlezero=false;
    bool doublezero=false;
    int ctr=0;
    F(i,0,n){
        F(j,0,m){
            if(mat[i][j]=='0'){
                singlezero=true;
                if(i-1>=0){
                    if(mat[i-1][j]=='0'){
                        doublezero=true;
                    }
                    if(j-1>=0 && mat[i-1][j-1]=='0'){
                        doublezero=true;
                    }
                    if(j+1<m && mat[i-1][j+1]=='0'){
                        doublezero=true;
                    }
                }
                if(j-1>=0 && mat[i][j-1]=='0') doublezero=true;
                if(i+1<n){
                    if(mat[i+1][j]=='0'){
                        doublezero=true;
                    }
                    if(j-1>=0 && mat[i+1][j-1]=='0'){
                        doublezero=true;
                    }
                    if(j+1<m &&  mat[i+1][j-1]=='0'){
                        doublezero=true;
                    }
                }
                if(j+1<m && mat[i][j+1]=='0') doublezero=true;
            }else{
                ctr++;
            }
        }
    }
    
    if(doublezero);
    else if(singlezero) ctr-=1;
    else ctr-=2;
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
