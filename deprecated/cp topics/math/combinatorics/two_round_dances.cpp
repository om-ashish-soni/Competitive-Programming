// problem link : https://codeforces.com/problemset/problem/1433/E
// solution : below code

int factorial(int n){
    int mul=1;
    while(n>1){
        mul*=n;
        n--;
    }
    return mul;
}


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int num=factorial(n-1);
    num*=2;
    num/=n;
    println(num);

    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
int factorial(int n){
    int mul=1;
    while(n>1){
        mul*=n;
        n--;
    }
    return mul;
}
