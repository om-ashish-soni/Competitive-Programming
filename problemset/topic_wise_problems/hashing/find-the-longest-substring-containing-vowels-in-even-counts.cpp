// problem link : https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/
// solution : below code

class Solution {
public:
    map<char,int> mp;
    int indexOf(char c){
        if(mp.count(c)){
            return mp[c];
        }   
        return -1; 
    }
    
    int findTheLongestSubstring(string ns) {
        mp['a']=0;
        mp['e']=1;
        mp['i']=2;
        mp['o']=3;
        mp['u']=4;
        int n=ns.size();
        map<string,int> mp;
        string s="00000";
        mp[s]=-1;
        int mx=0;
        for(int i=0;i<n;i++){
            int index=indexOf(ns[i]);
            if(index != -1){
                s[index]^=1;
            }
            if(mp.count(s)){
                int left=mp[s];
                int right=i;
                int window=right-left;
                mx=max(mx,window);
            }else{
                mp[s]=i;
            }
        }
        return mx;

    }
};