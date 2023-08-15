// problem link : https://leetcode.com/problems/camelcase-matching/description/
// solution : below code

class Solution {
public:
    bool lower(char ch){
        return ch >= 'a' && ch <= 'z';
    }
    bool upper(char ch){
        return !lower(ch);
    }

    bool match(string s,string p){
        int pi=0;
        for(auto c:s){
            if(pi>=p.size()){
                if(upper(c)) return false;   
            }else if(c == p[pi]){
                pi++;
            }else{
                if(upper(c)){
                    return false;
                }
            }
        }
        return pi>=p.size();
    }
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        int n=queries.size();
        vector<bool> arr(n);
        int i=0;
        for(auto & s:queries) arr[i++]=match(s,pattern);
        return arr;
    }
};