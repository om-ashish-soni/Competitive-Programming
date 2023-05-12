// problem link : https://leetcode.com/problems/permutation-sequence/description/
// solution : below code


#define ll long long
vector<ll> fact;
class Solution {
public:
    void init(){
        if(fact.size()==0){
            fact.push_back(1);
            for(int i=1;i<=10;i++){
                fact.push_back(fact.back()*i);
            }
        }
    }
    void get(string & s,int start,int k){
        int rest=s.size()-start-1;
        sort(s.begin()+start,s.end());
        if(k<2) return;
        if(k==2){
            swap(s[s.size()-1],s[s.size()-2]);
            return;
        }
        if(rest<2) return;
        int div=(k-1)/fact[rest];
        swap(s[start],s[start+div]);
        get(s,start+1,1+(k-1)%fact[rest]);
    }
    string getPermutation(int n, int k) {
        init();
        string s;
        for(int i=0;i<n;i++){
            s.push_back((char)('0'+i+1));
        }
        get(s,0,k);
        return s;
    }
};