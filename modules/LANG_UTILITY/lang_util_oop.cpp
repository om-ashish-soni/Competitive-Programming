class LangUtil{
public:
    static bool isalpha(char c){
        int ascii=(c-'a');
        return ascii>=0 && ascii<=25;
    }    
    static bool isdigit(char c){
        int ascii=(c-'0');
        return 0<=ascii && ascii<=9;
    }
    static bool islower(char c){
        return isalpha(c);
    }
    static bool isupper(char c){
        int ascii=(c-'A');
        return ascii>=0 && ascii<=25;
    }
    static bool isop(char c){
        string s="+-*/%";
        return s.find(c) != string::npos;
    }
    static vector<string> split(string s){
        vector<string> v;
        v.push_back("");
        for(auto c:s){
            if(c==' '){
                v.push_back("");
            }else{
                v.back().push_back(c);    
            }
            
        }
        return v;
    }
};
