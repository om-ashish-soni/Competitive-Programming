// problem link : https://leetcode.com/contest/weekly-contest-292/problems/largest-3-same-digit-number-in-string/
// solution : below code

class Solution {
public:
    string largestGoodInteger(string num) {
        int n=num.size();
        int mx=-1;
        string ans;
        for(int i=0;i<n-2;i++){
            string sub=num.substr(i,3);
            
            sort(begin(sub),end(sub));
            
            if(sub[0]==sub[2] and sub[0]-'0'>mx){
                // cout<<i<<" "<<sub<<" vs "<<sub[0]-'0'<<" "<<mx<<endl;
                ans=sub;
                mx=sub[0]-'0';
            }
        }
        return ans;
    }
};
