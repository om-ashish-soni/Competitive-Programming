// problem link : https://codeforces.com/problemset/problem/1603/A
// solution : below code

#define GCD(a,b) (__gcd((a),(b)))
#define LCM(a,b) ((a)*((b)/GCD((a),(b))))

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);

    int mylcm=1;
    int index=1;
    F(i,0,n){
        index++;
        mylcm=LCM(mylcm,index);
        if(v[i]%mylcm==0){
            YESNO1(false);
            return;
        }
    }
    YESNO1(true);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
