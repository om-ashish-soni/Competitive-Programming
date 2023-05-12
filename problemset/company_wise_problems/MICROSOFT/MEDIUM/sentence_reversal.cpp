// problem link : https://binarysearch.com/problems/Sentence-Reversal
// solution : below code

void reverseSubArray(vector<string>& v,int l,int r){
    while(l<r){
        swap(v[l],v[r]);
        l++;
        r--;
    }
    return;
}
vector<string> solve(vector<string>& sentence) {
    int l=0;
    int n=sentence.size();
    for(int i=0;i<n;i++){
        if(sentence[i]==" "){
            reverseSubArray(sentence,l,i-1);
            l=i+1;
        }
    }
    if(l<n) reverseSubArray(sentence,l,n-1);
    reverse(sentence.begin(),sentence.end());
    return sentence;
}
