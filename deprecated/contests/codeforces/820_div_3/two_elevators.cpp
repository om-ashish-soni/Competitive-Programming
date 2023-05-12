// problem link : https://codeforces.com/contest/1729/problem/A
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int a,b,c;
    read(a,b,c);
    int first=abs(a-1);
    int second=abs(b-c)+abs(c-1);
    if(first<second){
        cout<<1;
    }else if(second<first){
        cout<<2;
    }else{
        cout<<3;
    }
    println();
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
