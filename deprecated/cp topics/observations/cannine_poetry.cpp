// problem link : https://codeforces.com/problemset/problem/1466/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    string s;
    read(s);
    int n=s.size();
    int ctr=0;

    F(i,1,n){
        if(s[i]==s[i-1]){
            s[i]='A';
            ctr++;
        }else if(i>=2 && s[i]==s[i-2]){
            s[i]='A';
            ctr++;
        }
    }
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   

