class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> follower(n+1,0),following(n+1,0);
        for(auto &v:trust){
            follower[v[1]]++;
            following[v[0]]++;
        }
        for(int i=1;i<=n;i++){
            if(following[i]== 0 && follower[i] == n-1) return i;
        }
        return -1;
    }
};