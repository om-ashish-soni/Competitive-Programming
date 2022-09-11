// problem link : https://binarysearch.com/problems/Add-Binary-Numbers
// solution : below code

string solve(string a, string b) {
    int az=a.size();
    int bz=b.size();
    string c="";
    int carry=0;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    for(int i=0;i<max(az,bz);i++){
        int digit_a=0,digit_b=0;
        if(i<az) digit_a=(int)(a[i]-'0');
        if(i<bz) digit_b=(int)(b[i]-'0');
        int sum=digit_a+digit_b+carry;
        int digit_c=sum%2;
        carry=sum/2;
        c+=(char)(digit_c+'0');
    }
    if(carry==1) c+="1";
    reverse(c.begin(),c.end());
    return c;    
}
