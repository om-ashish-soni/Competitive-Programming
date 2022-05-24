// problem link : https://leetcode.com/problems/pascals-triangle/
// solution : below code

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> v;
        vector<int> row{1};
        v.push_back(row);
        for(int i=1;i<numRows;i++){
            vector<int> &prev=v.back();
            row.clear();
            row.push_back(1);
            int sz=prev.size();
            for(int j=1;j<sz;j++) row.push_back(prev[j]+prev[j-1]);
            row.push_back(1);
            v.push_back(row);
        }
        return v;
    }
};
