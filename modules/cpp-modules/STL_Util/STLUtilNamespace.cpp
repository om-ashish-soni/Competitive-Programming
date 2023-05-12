namespace STLUtil {
    template<typename T> void remove_duplicates_and_sort_vector(vector<T>& v){
        set<T> s(v.begin(),v.end());
        v.assign(s.begin(),s.end());
    }
}; // STLUtil
