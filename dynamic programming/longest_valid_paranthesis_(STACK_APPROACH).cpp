// problem link : 
// solution : below code
// approach : stack

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<pair<char,int>> stk;
        int index=1;
        int mx=0;
        stk.push({')',0});
        int n=s.size();
        vector<int> v(n+1,0);
        for(auto c:s){
            if(c=='('){
                stk.push({c,index});
            }else if(c==')'){
                if(stk.size()>0 && stk.top().first=='('){
                    pair<char,int> pr=stk.top();stk.pop();
                    int top=stk.top().second;
                    v[top]+=index-pr.second+1;
                }else{
                    stk.push({c,index});
                }
            }
            index++;
        }
        mx=*max_element(begin(v),end(v));
        return mx;
    }
};
