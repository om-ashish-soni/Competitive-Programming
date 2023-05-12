// Problem link : https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

// Solution : below code
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        vector<int> pref(1,0);
        vector<int> suff(1,0);
        int n=cardPoints.size();
        for(int i=0;i<k;i++){
            int len=pref.size();
            pref.push_back(pref[len-1]+cardPoints[i]);
            suff.push_back(suff[len-1]+cardPoints[n-1-i]);
        }
        int mx=cardPoints[0];
        for(int i=0;i<=k;i++){
            mx=max(pref[i]+suff[k-i],mx);
        }
        return mx;
    }
};
