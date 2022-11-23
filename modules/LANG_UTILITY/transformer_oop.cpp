class Transformer{
public: 
    static int ctoi(char c){
        return c-'0';
    }
    static char itoc(int i){
        return i-0+'0';
    }
    static char tolower(char c){
        int ascii=(int)(c-'A');
        char c1=(char)(ascii+'a');
        return c1;
    }
    static char toupper(char c){
        int ascii=(int)(c-'a');
        char c1=(char)(ascii+'A');
        return c1;
    }
};
