// problem link : https://codeforces.com/contest/1856/problem/D
// solution : below code

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

        int l=query[0];
        int r=query[1];
        validate();
        maxQueryLimit-=(r-l)*(r-l);

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
        int l=query[0]-1;
        int r=query[1]-1;

        int n=hidden.size();

        fenwickTree *fnt=new fenwickTree(n+10);
        
        int inv=0;

        for(int i=r;i>=l;i--){      
            int curr=hidden[i];
            inv+=fnt->get(curr);
            fnt->update(curr,1);
        }

        delete fnt;
        return inv;
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
        int provided=hidden[guessed[0]-1];
        int actual=*max_element(hidden.begin(),hidden.end());
        bool result =(provided==actual);
        cout<<"provided : "<<provided<<" vs actual : "<<actual<<endl;
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

namespace Solution {
    
    

    void solve(int testcase) {

        int n;
        read(n);
        
        bool mock=false;
        int maxQueryLimit=5*n*n;
        vi hidden(n);

        InteractiveJudge *judge=new InteractiveJudge(mock,maxQueryLimit,hidden);
        vi q={2,4};

        // int response=0;
        // judge->query(q,response);
        // cout<<"response : "<<response<<endl;

        int answer=n;


        for(int i=0;i<n-1;){
            // cout<<"i : "<<i+1<<endl;
            vi q1={i+1,i+2};
            int r1=0;
            judge->query(q1,r1);
            if(r1>0){
                bool valid=true;
                
                int addon=2;

                if(i+addon < n){
                    while(true){
                        bool flag=false;
                        int right=i+addon;
                        
                        if(right>n-1){
                            flag=true;
                            right=n-1;
                        }
                        int res1=0,res2=0;
                        vi q1={i+1,right+1};
                        vi q2={i+2,right+1};
                        judge->query(q1,res1);
                        judge->query(q2,res2);


                        // cout<<"res1 : "<<res1<<" => ";printv(q1);
                        // cout<<"res2 : "<<res2<<" => ";printv(q2);

                        int delta=res1-res2;
                        int expected=right-i;
                        // cout<<"delta : "<<delta<<" vs expected : "<<expected<<endl;

                        if(delta < expected){
                            valid=false;
                            break;
                        }
                        if(flag) break;

                        addon<<=1;

                    }
                }
                    
                if(valid){
                    answer=i+1;
                    break;
                }
                i+=addon/2;
                i++;
            }else{
                i++;
            }

        }

        judge->guess({answer});
        delete judge;
    }
};