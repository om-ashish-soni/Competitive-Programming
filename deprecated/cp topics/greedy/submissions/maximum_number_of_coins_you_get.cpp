// Problem link : https://leetcode.com/problems/maximum-number-of-coins-you-can-get/
// Problem type : Greedy
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(),piles.end());
        int sum=0;
        int left=0,right=piles.size()-1;
        while(left<right-1){
            sum+=piles[right-1];
            right-=2;
            left+=1;
        }
        return sum;
    }
};
