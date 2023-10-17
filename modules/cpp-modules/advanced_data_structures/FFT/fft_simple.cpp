class FFT{
    using cd=complex<double>;
    const double mathpi=MATHPI;
    public : 
    int sz=1;
    vector<cd> fa,fb;
    FFT(vector<int> &ma,vector<int> &mb){
        

        this->fa=vector<cd>(ma.begin(),ma.end());
        this->fb=vector<cd>(mb.begin(),mb.end());
        
        
        while(sz<ma.size()+mb.size()){
            sz<<=1;
        }
        fa.resize(sz);
        fb.resize(sz);


    }
    void fft(vector<cd> & a,bool invert){
        int n=a.size();
        if(n==1) return;
        vector<cd> a0(n/2),a1(n/2);
        for(int i=0;2*i<n;i++){
            a0[i]=a[2*i];
            a1[i]=a[2*i+1];
        }
        fft(a0,invert);
        fft(a1,invert);
        int sign=(invert)?(-1):(1);
        double ang=2*mathpi/n*sign;
        cd omega(1),mult(cos(ang),sin(ang));
        for(int i=0;2*i<n;i++){
            a[i]=a0[i]+omega*a1[i];
            a[i+n/2]=a0[i]-omega*a1[i];
            if(invert){
                a[i]/=2;
                a[i+n/2]/=2;
            }
            omega*=mult;
        }
        
    }
    vector<int> multiply(){
        fft(fa,false);
        fft(fb,false);
        for(int i=0;i<sz;i++){
            fa[i]*=fb[i];
        }
        fft(fa,true);
        vector<int> result(sz);
        for(int i=0;i<sz;i++){
            result[i]=round(fa[i].real());
        }
        return result;
    }
    static void how_to_use(){
        vector<int> a={1,2};
        vector<int> b={2,4,6};
        FFT *fft=new FFT(a,b);
        vector<int> c=fft->multiply();
        for(auto num:c) cout<<num<<" ";cout<<endl;
    }
};
