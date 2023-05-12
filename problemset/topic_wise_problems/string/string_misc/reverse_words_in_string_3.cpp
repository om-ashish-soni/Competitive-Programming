// problem link : https://leetcode.com/problems/reverse-words-in-a-string-iii/
// solution : below code

class Solution {
public:
    string reverseWords(string s) {
        string word="";
        vs v;
        for(auto c:s){
            if(c==' '){
                REVERSE(word);
                v.pb(word);
                word="";
            }else{
                word.pb(c);
            }
        }
        REVERSE(word);
        v.pb(word);
        string ns="";
        for(auto &word:v){
            ns+=word;
            ns+=" ";
        }
        ns.pop_back();
        return ns;
    }
};
