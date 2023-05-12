/*
    link of problem:
    https://leetcode.com/problems/jump-game-iii/submissions/
*/

class Solution {
public:
    void canReach(vector<int> &arr,vector<int>& memo,int start,int ctr=0){
        if(ctr >= arr.size()) throw false;
        if(start>=arr.size()) return;
        if(start<0) return;
        if(arr[start] == 0) throw true;
        if(memo[start] != -1) return;
        ctr++;
        memo[start]=1;
        canReach(arr,memo,start+arr[start],ctr);
        canReach(arr,memo,start-arr[start],ctr);
        return;
    }
    bool canReach(vector<int>& arr, int start) {
        vector<int> memo(arr.size(),-1);
        try{canReach(arr,memo,start);}
        catch(bool b){cout<<endl;return b;}
        return false;
    }
};