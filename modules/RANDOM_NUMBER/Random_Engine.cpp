
class RandomEngine{
    mt19937 mt;
public:
    RandomEngine(){
        mt19937 smt(time(nullptr));
        this->mt=smt;
    }
    
    int get(){
        return mt();
    }
    int get(int n){
        return get()%n;
    }
    int get(int l,int r){
        int window=r-l+1;
        return get(window)+l;
    }
    static void how_to_use(){
        RandomEngine *rng=new RandomEngine();
        cout<<rng->get()<<endl;
        cout<<rng->get(10)<<endl;
        cout<<rng->get(20,30)<<endl;
    }
};
