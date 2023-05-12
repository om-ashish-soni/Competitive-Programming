// problem link : https://leetcode.com/problems/data-stream-as-disjoint-intervals/description/
// solution : below code


class SummaryRanges {
public:
    bool change=false;
    set<pair<int,int>> st;
    SummaryRanges() {
    }
    
    void addNum(int value) {
        change=true;
        auto left=st.lower_bound({value,value});
        auto right=st.upper_bound({value,value});
        bool first=false;
        bool second=false;
        if(left != st.begin()){
            left--;
            if(left->first <= value && value <= left->second){
                return;
            }
            first=((left->second+1) == value);
        }
        
        if(right != st.end()){
            if(right->first <= value && value <= right->second){
                return;
            }
            second=(value+1 == (right->first));
        }
        cout<<"value : "<<value<<endl;
        cout<<first<<" , "<<second<<endl;
        if(first && second){
            st.insert({left->first,right->second});
            st.erase(left);
            st.erase(right);
        }else if(first){
            st.insert({left->first,value});
            st.erase(left);
        }else if(second){
            st.insert({value,right->second});
            st.erase(right);
        }else{
            st.insert({value,value});
        }
    }
    
    vector<vector<int>> getIntervals() {
        change=false;
        vector<vector<int>> v(st.size());
        int index=0;
        for(auto & pr:st){
            v[index++]={pr.first,pr.second};
        }
        return v;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */  