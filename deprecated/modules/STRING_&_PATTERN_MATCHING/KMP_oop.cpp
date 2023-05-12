class KMP{
public:
    string s;
    int n;
    vector<int> lps;
    KMP(string s){
        this->s=s;
        this->n=this->s.size();
        this->lps.assign(n,0);
        buildLPS();
    }
    void buildLPS(){
        for(int i=1;i<n;i++){
            int j=lps[i-1];
            while(j>0 && s[i] != s[j]){
                j=lps[j-1];
            }
            if(s[i]==s[j]) j++;
            // cout<<"i : "<<i<<" , s[i] : "<<s[i]<<" , j : "<<j<<endl;
            lps[i]=j;
        }
    }
    vector<int> getLPS(){
        return lps;
    }
    vector<int> findIn(string & text){
        vector<int> founds;
        int k=0;
        int textsize=text.size();
        for(int i=0;i<textsize;i++){
            while(k>0 && text[i] != s[k]){
                k=this->lps[k-1];                
            }
            if(text[i]==s[k]){
                k++;
            }
            if(k==n){
                
                int index=i-n+1;
                // cout<<"found at : "<<index<<endl;
                k=this->lps[k-1];
                founds.push_back(index);
            }
        }
        return founds;
    }
    static vector<int> find(string & text,string & pattern){
        KMP *kmp=new KMP(pattern);
        vector<int> founds=kmp->findIn(text);
        delete kmp;
        return founds;
    }
    static void how_to_use(){
        string text="ABABDABACDABABCABAB";
        string pattern="ABABCABAB";
        vector<int> founds=KMP::find(text,pattern);
        int index=-1;
        if(founds.size()==0){
            index=-1;
            cout<<index<<endl;
        }else{
            int firstIndex=founds.front();
            int lastIndex=founds.back();
            cout<<firstIndex<<" , "<<lastIndex<<endl;
        }
    }
};
