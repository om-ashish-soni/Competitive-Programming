// problem link : https://leetcode.com/problems/koko-eating-bananas/
// solution : below code
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        
        int r=1+(*max_element(piles.begin(),piles.end()));
        int l=1;
        int ans=-1;
        while(l<r){
            long long tm=0;
            int mid=(l+r)/2;
            for(long long pile : piles){
                tm+=ceil((long double)pile/(long double)mid);
            } 
            if(tm>h) l=mid+1;
            else{r=mid;ans=mid;}
        }
        return ans;
    }
};
