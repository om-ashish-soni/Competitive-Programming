// problem link : https://codeforces.com/problemset/problem/1717/C
// explaination : 
    This problem is about observation.

    given two arrays a and b , the observation are :
    next cyclic index can be written as (i+1)%n .

        if a[i] > b[i] , then no possible way to convert a to b , hence answer is NO.
        if a[i] == b[i] , then we can skip this index and move to next index.
        if a[i] < b[i] , then we can increment a[i] until a[i]<=a[(i+1)%n] , means we need to check whether b[i]-b[(i+1)%n] > 1 ,then there is no possible way , even if we increment a[i] or a[(i+1)%n] ,
        then also we can not take a[i] to b[i] with incrementing , since there is limit that b[i]-b[(i+1)%n] is greater than 1, so no way possible , hence answer is NO.

    If all these 3 cases does not rejects answer , means there is an answer YES.

    below is my implementation.
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v1(n),v2(n);
    readv(v1);
    readv(v2);
    F(i,0,n){
        int next=(i+1)%n;
        if(v1[i] > v2[i]){
            YESNO1(false);
            return;
        }
        if(v1[i]<v2[i]){
            if(v2[i]-v2[next]>1){
                YESNO1(false);
                return;
            }
        }
    }
    YESNO1(true);
    // kick(t);
    
    // write your answer here
    // println(pref);
    
    //complete your answer here
    // println();
}   
