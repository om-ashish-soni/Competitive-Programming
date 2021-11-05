class Solution {
public:
    static bool comp(pair<int,char> p1,pair<int,char> p2){
        return p1.first>p2.first;
    }
    string frequencySort(string s) {
        unordered_map<char,int> ump;
        vector<pair<int,char>> v;
        for(int i=0;i<s.size();i++) ump[s[i]]++;
        for(auto it=ump.begin();it!=ump.end();++it) v.push_back({it->second,it->first});
        sort(v.begin(),v.end(),comp);
        s="";
        for(auto elem:v) for(int i=0;i<elem.first;i++) s+=elem.second;
        return s;
    }
};