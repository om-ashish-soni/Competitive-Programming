// problem link  : https://codeforces.com/problemset/problem/1443/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int a,b;
    read(a,b);
    string s;
    read(s);
    int n=s.size();
    int start=s.find('1');
    int cost=0;

    if(start>=0 && start<n){
        cost=a;
        while(start<n && s[start]=='1') start++;
        int zeros=0;
        int ones=0;
        F(i,start,n){
            if(s[i]=='1'){
                if(s[i-1]=='0'){
                    cost=cost+min(a,b*zeros);
                    zeros=0;    
                }
            }else{
                zeros++;
            }
        }
    }
    println(cost);


    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
