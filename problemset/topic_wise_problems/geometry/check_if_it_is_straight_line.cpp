// problem link : https://leetcode.com/problems/check-if-it-is-a-straight-line/description
// solution : below code

class Solution {

public:

    bool judge(vector<vector<int>>& v) {

        int n=v.size();

        for(int i=2;i<n;i++){

            vector<int> last=v[i-1];

            vector<int> curr=v[i];

            if(last[0]*curr[1] == last[1]*curr[0]) ;

            else return false;

        }

        return true;

    }

    bool checkStraightLine(vector<vector<int>>& v) {

        int n=v.size();

        

        for(int i=n-1;i>0;i--){

            v[i][0]-=v[i-1][0];

            v[i][1]-=v[i-1][1];

        }

        return judge(v);

    }

};