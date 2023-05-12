// problem link : https://leetcode.com/problems/total-appeal-of-a-string/
// solution : below code

class Solution {
public:
    long long appealSum(string s) {
        long long n=s.size();
        long long inc=1,dec=n;
        long long ideal=0;
        for(long long i=inc;i<=n;i++){
            ideal+=inc*dec;
            dec--;
            inc++;
        }
        unordered_map<char,long long> hash;
        for(long long i=0;i<n;i++){
            if(hash.count(s[i])){
                long long rem=n-i;
                long long pending=hash[s[i]]+1;
                ideal-=pending*rem;
            }
            hash[s[i]]=i;
        }
        cout<<ideal<<endl;
        return ideal;
    }
};
