class Converter{
    public:
    static int ctoi(char c){
        return c-'0';
    }
    static char itoc(int i){
        return i-0+'0';
    }
};

class BigAdder{

    public : 
    static string add(string a,string b){

        int addon=0;
        string s;
        while(a.size()>0 && b.size()>0){

            int first=Converter::ctoi(a.back());
            int second=Converter::ctoi(b.back());
            a.pop_back();
            b.pop_back();
            int sm=first+second+addon;
            int digit=sm%10;
            addon=sm/10;
            s.push_back(Converter::itoc(digit));
        }
        while(a.size()>0){
            int first=Converter::ctoi(a.back());
            a.pop_back();
            int sm=first+addon;
            int digit=sm%10;
            addon=sm/10;
            s.push_back(Converter::itoc(digit));
        }
        while(b.size()>0){
            int first=Converter::ctoi(b.back());
            b.pop_back();
            int sm=first+addon;
            int digit=sm%10;
            addon=sm/10;
            s.push_back(Converter::itoc(digit));
        }
        if(addon>0) s.push_back(Converter::itoc(addon));
        reverse(s.begin(),s.end());
        return s;
    }
};
void solve(){
    
    string a,b;
    std::cin>>a>>b;
    string s=BigAdder::add(a,b);
    std::cout<<s<<endl;
}
