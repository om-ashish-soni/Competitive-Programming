// problem link : https://leetcode.com/problems/average-waiting-time/
// solution : below code


class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& v) {
        double sm=0;
        int tm=0;
        FEACH(row,v){
            // cout<<"tm : "<<tm<<" vs "<<row[0]<<endl;
            if(tm>row[0]){
                sm+=(tm-row[0]);
            }
            // cout<<"wait time : "<<sm<<endl;
            tm=max(tm,row[0]);
            // cout<<"start time : "<<tm<<endl;
            tm+=row[1];
            sm+=row[1];
            // cout<<"finish time : "<<tm<<endl;
        }
        int n=v.size();
        sm/=n;
        // cout<<"answer : "<<sm<<endl;
        return sm;
    }
};
