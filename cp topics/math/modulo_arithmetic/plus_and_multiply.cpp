// problem link : https://codeforces.com/problemset/problem/1542/B
// solution : below code

void solve(int t){
    //shree ganeshay namah
    // println("shree ganeshay namah");
    // println("shreepad rajam sharanam prapadhye");

    int n,a,b;
    read(n,a,b);
    map<int,bool> mp;

    int key=1;
    mp[key]=true;
    int last=-1;
    while(key*a<=n && last != key){
        last=key;
        key=key*a;
        mp[key%b]=true;
    }
    bool res=mp[n%b];
    YESNO2(res);

    // println("shree ganeshay namah");
    // println("shreepad rajam sharanam prapadhye");

}
