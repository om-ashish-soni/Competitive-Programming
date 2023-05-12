// problem link : https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/description/
// solution : below code

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int ctr=0;
        for(auto & s:patterns){
            if(word.find(s) != string::npos){
                ctr++;
            }
        }
        return ctr;
    }
};