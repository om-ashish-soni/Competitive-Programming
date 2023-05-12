class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> v;
        vector<int> last(2,1),curr(1,1);
        v.push_back(curr);
        if(numRows==1) return v;
        v.push_back(last);
        curr.clear();
        for(int i=2;i<numRows;i++){
            int first=1,end=1;
            curr.push_back(1);
            for(int j=1;j<i;j++){
                curr.push_back(last[j-1]+last[j]);
            }
            curr.push_back(1);
            last=curr;
            curr.clear();
            v.push_back(last);
        }
        return v;
    }
};