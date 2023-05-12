// problem link : https://leetcode.com/problems/remove-all-occurrences-of-a-substring/description/
// solution : below code

class Solution {
public:
    string removeOccurrences(string s, string part) {
        string mys;
        for(auto c:s){
            mys.push_back(c);
            int sz=mys.size();
            int pz=part.size();
            int i=sz-1,j=pz-1;
            for(;j>=0 && i>=0;i--,j--){
                if(part[j] != mys[i]) break;
            }
            if(j==-1){
                for(int i=0;i<pz;i++){
                    mys.pop_back();
                }
            }
        }
        return mys;
    }
};