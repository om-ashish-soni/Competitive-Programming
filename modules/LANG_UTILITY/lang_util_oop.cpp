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
};
