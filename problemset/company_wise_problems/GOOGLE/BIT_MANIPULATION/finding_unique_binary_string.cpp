// problem link : https://leetcode.com/problems/find-unique-binary-string/
// solution : below code

class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        map<string,bool> mp;
        for(auto num:nums) mp[num]=true;
        int n=nums.front().size();
        int start=0;
        int end=n+1;
        for(int i=start;i<end;i++){
            bitset<32> bs(i);
            string s=bs.to_string();
            reverse(s.begin(),s.end());
            s=s.substr(0,n);
            reverse(s.begin(),s.end());
            if(mp.count(s)==0) return s;
        }
        return "";
    }
};
