// problem link : https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/description/
// solution : below code

class Solution {
public:
    string removeDuplicates(string s) {
        string output;
        for(auto c:s){
            if(output.size()>0 && c==output.back()){
                while(output.size()>0 && c==output.back()){
                    output.pop_back();
                }
            }else{
                output.push_back(c);
            }
        }
        return output;
    }
};