class Manacher{
    string s;
    int n;
    vector<int> palCount;
    int mxIndex=-1,mx=0;
    string longestPalindrome;
public: 
    void buildString(string str){
        for(auto c:str){
            s+="$";
            s+=c;
        }
        s+="$";
    }
    Manacher(string s){
        this->n=s.size();
        this->n=2*n+1;
        this->buildString(s);
        palCount=*new vector<int>(n,0);
        this->process();
    }
    void process(){
        int iter=0;
        int start(0),end(0);
        for(int i=0;i<n;){
            while(start>0 && end<n-1 && s[start-1]==s[end+1]){
                start--;
                end++;
            }
            palCount[i]=end-start+1;
            if(end==n-1) break;
            int newCenter=end + ((i%2 == 0)?(1):(0));
            for(int j=i+1;j<=end;j++){
                palCount[j]=min(palCount[i-(j-i)],2*(end-j)+1);
                if(j+palCount[i-(j-i)]/2 == end){
                    newCenter=j;
                    break;
                }
            }
            i=newCenter;
            end=i+palCount[i]/2;
            start=i-palCount[i]/2;
        }
        for(int i=0;i<n;i++){
            if(palCount[i] >mx){
                mx=palCount[i];
                mxIndex=i;
            }
        }
        longestPalindrome=s.substr(mxIndex-mx/2,mx);
        string dummy=longestPalindrome;
        longestPalindrome="";
        for(auto c:dummy){
            if(c!='$') longestPalindrome+=c;
        }
    }
    void print(){
        for(int i=0;i<n;i++){
            cout<<i<<" : "<<palCount[i]<<endl;
        }
    }
    int getLen(){
        return mx/2;
    }
    string getPal(){
        return longestPalindrome;
    }
    string getMaxPalPrefix(){
        int index=-1;
        for(int i=0;i<n;i++){
            int left=i-palCount[i]/2;
            // cout<<s[i]<<" : "<<palCount[i]<<endl;
            if(left<=0){
                index=i;
            }
        }
        string pal_prefix;
        for(int i=0;i<2*index;i++){
            if(s[i] != '#' && s[i] != '$'){
                pal_prefix.push_back(s[i]);
            }
        }
        return pal_prefix;
    }
};