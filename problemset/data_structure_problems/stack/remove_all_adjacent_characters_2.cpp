// problem link : https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/description/
// solution : below code

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char,int>> stk;
        
        for(auto c:s){
            if(stk.size()>0 && stk.top().first==c){
                stk.top().second++;
                
            }else{
                stk.push({c,1});
            }
            if(stk.size()>0){
                if(stk.top().second>=k){
                    stk.pop();
                }
            }
        }
        string output;
        while(stk.size()>0){
            pair<char,int> pr=stk.top();
            stk.pop();
            char ch=pr.first;
            int freq=pr.second;
            while(freq--){
                output.push_back(ch);
            }
        }
        reverse(output.begin(),output.end());
        return output;
    }
};