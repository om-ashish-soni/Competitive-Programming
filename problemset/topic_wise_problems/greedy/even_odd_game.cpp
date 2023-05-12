// problem link : https://codeforces.com/problemset/problem/1472/D
// solution : below code


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    SORT(v);
    REVERSE(v);
    int bit=0;
    int a=0,b=0;
    F(i,0,n){
        int score=(v[i]%2 == bit)?(v[i]):0;
        if(bit==0){
            a+=score;
        }else{
            b+=score;
        }
        bit=(bit xor 1);
    }
    if(a>b){
        println("Alice");
    }else if(b>a){
        println("Bob");
    }else{
        println("Tie");
    }
    
    // kick(t);
    
    // write your answer here
    // println(pref);
    
    //complete your answer here
    // println();
}   
    
