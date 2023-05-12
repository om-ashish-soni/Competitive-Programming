// problem link : https://leetcode.com/problems/reverse-only-letters/description/
// solution : below code

class Solution {
public:
    string reverseOnlyLetters(string s) {
        vector<int> pos;
        int n=s.size();
        int i=-1;
        for(auto c:s){
            i++;
            if(c>=65 && c<=90 || c>=97 && c<=122){
                pos.push_back(i);
            }
        }
        int sz=pos.size();
        for(int j=0;j<sz/2;j++){
            swap(s[pos[j]],s[pos[sz-j-1]]);
        }
        return s;
    }
};