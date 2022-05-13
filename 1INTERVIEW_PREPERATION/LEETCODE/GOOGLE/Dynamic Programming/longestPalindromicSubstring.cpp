// problem link : https://leetcode.com/problems/longest-palindromic-substring/
// solution : below code

class Solution {
public:
    
    string longestPalindrome(string s) {
        int n=s.size();
        bool isPalindrome[n+1][n+1];
        for(int i=0;i<n;i++){
            isPalindrome[i][i]=true;
            for(int j=i+1;j<n;j++){
                isPalindrome[i][j]=false;
            }
        } 
        int mx=1,l=0;
        for(int j=0;j<n;j++){
            for(int i=0;i<j;i++){
                if(s[i]==s[j] and (i+1>=j-1 || isPalindrome[i+1][j-1])){
                    isPalindrome[i][j]=true;
                    if(mx<j-i+1){
                        l=i;
                        mx=j-i+1;
                    }
                }
            }
        }
        return s.substr(l,mx);
    }
};
