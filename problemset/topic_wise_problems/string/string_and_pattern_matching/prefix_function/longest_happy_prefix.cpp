// problem link : https://leetcode.com/problems/longest-happy-prefix/description/
// solution : below code

class Solution {
public:
void prefix_function(string s,vector<int>& pf){
	int n=s.size();
	pf.resize(n);
	pf[0]=0;
	for(int i=1;i<n;i++){
		int j=pf[i-1];
		while(j>0 && s[i]!=s[j]){
			j=pf[j-1];  
		}
		if(s[i]==s[j]){
			j++;
		}
		pf[i]=j;
	}
	// Time complexity : O(n)
}

    string longestPrefix(string s) {
        vector<int> pf;
        prefix_function(s,pf);
        return s.substr(0,pf[s.size()-1]);
    }
};