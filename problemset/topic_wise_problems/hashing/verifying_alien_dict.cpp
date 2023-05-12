// problem link : https://leetcode.com/problems/verifying-an-alien-dictionary/description/
// solution : below code

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        map<char,int> mp;
        int i=0;
        for(char c='a';c<='z';c++,i++){
            mp[order[i]]=c;
        }
        for(auto & word:words){
            
            for(int i=0;i<word.size();i++){
                word[i]=mp[word[i]];
            }
            // cout<<word<<" ";
        }
        for(int i=1;i<words.size();i++){
            if(words[i-1]>words[i]) return false;
        }
        return true;
    }
};