// problem link : https://leetcode.com/problems/valid-perfect-square/description/
// solution : below code

class Solution {
public:
    bool isPerfectSquare(int num) {
        long long l=1;
        long long r=num;
        while(l<=r){
            bool flag=(l==r);
            long long mid=(l+r)/2;
            long long key=(mid*mid);
            if(key==num) return true;
            else if(key<num){
                l=mid+1;
            }else{
                r=mid;
            }
            if(flag) break;
        }
        return false;
    }
};