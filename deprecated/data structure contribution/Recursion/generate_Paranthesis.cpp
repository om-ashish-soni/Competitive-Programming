class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string s="()";
        vector<string> v=*(new vector<string>);
        unordered_set<string> storageSet;
        if(n==1){ 
            v.push_back(s);
            return v;
        }
        vector<string> childStrings=generateParenthesis(n-1);
        for(auto &childStr:childStrings){
            int found=childStr.find('(');
            string first,last;
            first=s;
            last=childStr;
            first+=childStr;
            storageSet.insert(first);
            while(found < childStr.size()){
                string prefix=childStr.substr(0,found+1);
                string suffix=childStr.substr(found+1);
                prefix+=s;
                prefix+=suffix;
                storageSet.insert(prefix);
                found=childStr.find('(',found+1);
            }
            last+=s;
            storageSet.insert(last);
        }
        for(auto it=storageSet.begin();it!=storageSet.end();++it){
            v.push_back(*it);
        }
        return v;
    }
};