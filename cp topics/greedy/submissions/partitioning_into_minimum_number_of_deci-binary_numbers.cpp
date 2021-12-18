// Problem link : https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
// Problem type : greedy
class Solution {
public:
    int minPartitions(string s) {
        int ans=(int)(*max_element(s.begin(),s.end())-48);
        return ans;
    }
};
