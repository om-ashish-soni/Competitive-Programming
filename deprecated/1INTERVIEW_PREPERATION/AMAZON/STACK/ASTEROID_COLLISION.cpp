// problem link : https://leetcode.com/problems/asteroid-collision/
// solution : below code

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& a) {
        int n=a.size();
        vector<int> v;
        stack<pair<int,int>> s;
        vector<int> rem;
        for(int i=n-1;i>=0;i--){
            if(a[i]>0){
                int positive=a[i];
                vector<pair<int,int>> to_be_removed;
                while(s.size()>0){
                    auto elem=s.top();
                    if(abs(elem.first)<positive){
                        s.pop();
                        to_be_removed.push_back(elem);
                    }
                    else if(abs(elem.first)==positive){
                        s.pop();
                        to_be_removed.push_back(elem);
                        rem.push_back(i);
                        break;
                    }
                    else{
                        rem.push_back(i);
                        break;
                    }
                }
                for(auto num:to_be_removed){
                    rem.push_back(num.second);
                }
            }else{
                s.push({-a[i],i});
            }
            
        }
        for(auto index:rem){
            a[index]=0;
        }
        for(int i=0;i<n;i++){
            if(a[i]!=0) v.push_back(a[i]);
        }
        return v;
    }
};
