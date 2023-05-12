// problem link : https://leetcode.com/problems/bitwise-and-of-numbers-range/
// solution : below code

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        ll diff=right-left;        
        ll mul=1;
        ll ans=0;
        F(i,0,32){
            if(diff<mul){
                if((left&mul)>0 && (right&mul)>0){
                    ans+=mul;    
                }
            }
            mul<<=1;
        }
        return ans;
    }
};
