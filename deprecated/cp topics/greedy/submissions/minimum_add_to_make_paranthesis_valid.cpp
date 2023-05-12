// Problem link : https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
// Problem type : Greedy
class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> stk;
        int moves=0;
        for(char c:s){
            if(c=='('){
                stk.push(c);
            }else{
                if(stk.size()>0){
                    stk.pop();
                }else moves++;
            }
        }
        moves+=stk.size();
        return moves;
    }
};
