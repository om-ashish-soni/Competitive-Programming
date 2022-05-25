// problem link : https://www.interviewbit.com/problems/repeat-and-missing-number-array/
// solution : below code

vector<int> Solution::repeatedNumber(const vector<int> &A) {
    long long n1=A.size();
    vector<bool> v(n1,false);

    long long total=(n1*(n1+1)/2);
    long long sm=0;
    int repeat=-1;
    int missing=-1;
    for(int i=0;i<n1;i++){
        if(v[A[i]]){
            repeat=A[i];
            sm-=A[i];
        }
        v[A[i]]=true;
        sm+=A[i];
    }
    missing=total-sm;
    vector<int> len1{repeat,missing};
    return len1;
}
