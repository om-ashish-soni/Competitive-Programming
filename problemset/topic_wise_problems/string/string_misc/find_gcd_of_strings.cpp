// problem link : https://leetcode.com/problems/greatest-common-divisor-of-strings/description/
// solution : below code

class Solution {
public:
    bool get(string text,string key){
        int div=text.size()/key.size();
        int ctr=0;
        int last=-key.size();
        while(true){
            int index=text.find(key,last+key.size());
            if(index != string::npos){
                ctr++;
                last=index;
            }else{
                break;
            }
        }
        return ctr==div;
    }
    string gcdOfStrings(string str1, string str2) {
        if(str2.size()>str1.size()){
            swap(str2,str1);
        }
        string key=str2;
        string text=str1;
        int mysz=str2.size();
        while(key.size()>0){
            if(mysz%key.size() ==0 && text.size()%key.size()==0){
                bool res= get(str1,key) && get(str2,key);
                if(res) return key;
            }
            key.pop_back();
        }
        return key;
    }
};