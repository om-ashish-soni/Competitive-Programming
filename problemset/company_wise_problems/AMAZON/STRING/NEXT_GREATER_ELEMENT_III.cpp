// problem link : https://leetcode.com/problems/next-greater-element-iii/
// solution : below code

class Solution {
public:
    string itos(int num){
        ostringstream ostr;
        ostr<<num;
        return ostr.str();
    }
    void next_perm(string &s){
        cout<<"before : "<<s<<endl;
        int mx_index=s.size()-1;
        for(int i=s.size()-2;i>=0;i--){
            if(s[mx_index]<=s[i]){
                mx_index=i;
            }else{
                sort(s.begin()+i+1,s.end());
                int index=upper_bound(s.begin()+i+1,s.end(),s[i])-(s.begin());
                swap(s[i],s[index]);
                sort(s.begin()+i+1,s.end());
                break;
            }
        }
        cout<<"after : "<<s<<endl;
    }
    int nextGreaterElement(int n) {
        const int range=pow(2,31)-1;
        string num=itos(n);
        next_perm(num);
        long long output=stoll(num);
        if(output>range) return -1;
        if(output<=n) return -1;
        return output;
    }
};
