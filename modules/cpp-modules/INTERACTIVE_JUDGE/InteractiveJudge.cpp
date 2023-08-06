class InteractiveJudge {
public:
    bool mock=true;
    int maxQueryLimit=0;


    vector<int> hidden;

    InteractiveJudge(bool mock,int maxQueryLimit,vector<int> hidden){
        this->hidden=hidden;
        this->mock=mock;
        this->maxQueryLimit=maxQueryLimit;
        init();
    }

    void init(){
        if(mock){
            // this can be mocked .... 
            for(int i=0;i<hidden.size();i++){
                cin>>hidden[i];
            }
        }
    }

    void validate(){
        if(maxQueryLimit<=0){
            cout<<"Max Query Limit Exceeded"<<endl;
            exit(0);
        }
    }

    void query(vector<int> & query,int & response){

        validate();
        maxQueryLimit--;

        if(mock){
            response=mockQuery(query);
        }else{
            printQuery(query);
            readResponse(response);
        }
    }

    int mockQuery(vector<int> & query){
        // perform query operation and return result
        // this processing should be dynamic .... 

        int xorr=0;
        for(auto index:query){
            xorr^=(hidden[index-1]);
        }

        return xorr;
    }


    void printQuery(vector<int> & query){
        cout<<"? ";
        for(auto num:query){
            cout<<num<<" ";
        }
        cout<<endl;
    }

    void guess(const vector<int> & guessed){
        if(mock){
            mockGuess(guessed);
        }else{
            printGuess(guessed);
        }
    }

    void mockGuess(const vector<int> & guessed){
        bool result =(hidden==guessed);
        cout<<"result : "<<result<<endl;
    }


    void printGuess(const vector<int> & guessed){
        cout<<"! ";
        for(auto num:guessed){
            cout<<num<<" ";
        }
        cout<<endl;
    }

    void readResponse(int & response){
        cin>>response;
    }

    static void how_to_use(){
        bool mock=true;
        int maxQueryLimit=10;

        vector<int> hidden={1,0,1};

        InteractiveJudge *judge=new InteractiveJudge(mock,maxQueryLimit,hidden);

        // take some input here
        vector<int> que={1,2};
        
        int response;

        judge->query(que,response);

        cout<<"response : "<<response<<endl;

        judge->guess(vector<int>{1,0,1});
    }
};
