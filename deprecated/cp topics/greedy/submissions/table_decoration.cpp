// problem link : https://codeforces.com/problemset/problem/478/C
// solution : below code

void solve(int t){
    //shree ganeshay namah
    // println("shree ganeshay namah");
    // println("shreepad rajam sharanam prapadhye");

    vector<int> v(3);
    readv(v);
    SORT(v);
    REVERSE(v);
    if(v[0]>=2*(v[1]+v[2])){
        cout<<v[1]+v[2]<<endl;
    }else{
        cout<<(v[0]+v[1]+v[2])/3<<endl;
    }
  
    // println("shree ganeshay namah");
    // println("shreepad rajam sharanam prapadhye");

}
