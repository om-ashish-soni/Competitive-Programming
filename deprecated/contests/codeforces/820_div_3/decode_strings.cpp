// problem link : https://codeforces.com/contest/1729/problem/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    string s;
    read(s);
    string key;
    for(int i=n-1;i>=0;){
        char c;
 
        if(s[i]=='0'){
            // cout<<s[i-2]<<" , "<<s[i-1]<<endl;
            c=(char)tochar(s[i-2],s[i-1]);
            i-=3;
        }else{
            c=(char)('a'+(s[i]-'0')-1);
            i--;
        }
        key.push_back(c);
    }
    REVERSE(key);
    println(key);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
