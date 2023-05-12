Problem link: https://leetcode.com/problems/longest-substring-without-repeating-characters/
Problem type: Sliding window

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size()<1) return s.size();
        int window=1;
        int l,r;
        l=r=0;
        unordered_map<int,int> hash;
        hash[s[l]]++;
        while(r<s.size()){
           // cout<<l<<" "<<r<<" "<<"s[r] "<<s[r]<<" "<<hash[s[r]]<<" ";
           if(l>=r){
               // cout<<window<<" case 1"<<endl;
               r++;
               if(r<s.size()) hash[s[r]]++;
           }
           else if(hash[s[r]]>1){
                // cout<<window<<" case 2"<<endl;
                hash[s[l]]--;
                l++;
            }else{
                // cout<<window<<" case 3"<<endl;
                window=max(window,r-l+1);
                r++;
                if(r<s.size()) hash[s[r]]++;
            }
        }
        
        return window;
    }
};
