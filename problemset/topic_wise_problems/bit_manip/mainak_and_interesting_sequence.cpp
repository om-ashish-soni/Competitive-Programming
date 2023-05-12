// problem link : https://codeforces.com/problemset/problem/1726/B
// rating : 1100
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    

    int n;
    read(n);
    int m;
    read(m);
    if(n>m){
        YESNO2(false);
        return;
    }
    if(n%2==0){
        if((m-n+2)%2==0){
            YESNO2(true);
            int one=1;
            int div=(m-n+2)/2;
            F(i,0,n-2) print(one);
            println(div,div);
            return;
        }else{
            YESNO2(false);
            return;
        }
    }else{
        YESNO2(true);
        int one=1;
        int rem=m-(n-1);
        F(i,0,n-1) print(one);
        println(rem);
        return;
    }

    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
