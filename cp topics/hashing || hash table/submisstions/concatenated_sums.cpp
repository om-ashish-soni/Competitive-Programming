// problem link : https://binarysearch.com/problems/Concatenated-Sums
// solution : below code

string intToString(int n){
    ostringstream ostr;
    ostr<<n;
    return ostr.str();
}
int stringToInt(string &s){
    stringstream ss(s);
    int x;
    ss>>x;
    return x;
}
int solve(vector<int>& nums) {
    int sm=0;
    int n=nums.size();
    unordered_map<int,int> hash;
    for(auto num:nums){
        int key=intToString(num).size();
        hash[key]++;
        sm+=n*num;
    }
    for(auto num:nums){
        for(auto &pr:hash){
            int mult=ceil(pow(10,pr.first));
            sm+=pr.second*mult*num;
        }
    }
    return sm;
}
