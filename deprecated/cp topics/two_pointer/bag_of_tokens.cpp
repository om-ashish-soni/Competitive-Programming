// problem link : https://leetcode.com/problems/bag-of-tokens/
// solution : below code

class Solution {
public:
    int bagOfTokensScore(vector<int>& v, int power) {
        if(v.size()==0) return 0;
        sort(v.begin(),v.end());
        int score=0;
        int n=v.size();
        int l=0;
        int r=n-1;
        while(l<r){
            // cout<<l<<" : "<<power<<" vs "<<v[l]<<" , score : "<<score<<endl;
            if(power>=v[l]){
                // cout<<"greater : "<<endl;
                power-=v[l];
                score++;
                l++;
            }else{
                // cout<<"lesser : "<<endl;
                if(score>0){
                    score--;
                    power+=v[r];
                    r--;
                }else{
                    break;
                }
            }
        }
        if(power>=v[l]) score++;
        return score;
    }
};
