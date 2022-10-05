// problem link : https://codeforces.com/problemset/problem/1594/B
// solution : below code

#define MOD1 1000000007
int modMul(int a,int b,int mod){
  return ((a%mod)*(b%mod))%mod;
}
int modAdd(int a,int b,int mod){
  return ((a%mod)+(b%mod))%mod;
}
void solve(int t){
  //shree ganeshay namah
  // println("shree ganeshay namah");
  int n,k;
  read(n,k);
  bitset<60> bs(k);
  int mul=1;
  int num=0;
  F(i,0,60){
    if(bs[i]==1) num=modAdd(num,mul,MOD1);
    mul=modMul(mul,n,MOD1);
  }    
  println(num);

  // print answers here

}
