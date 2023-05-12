#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;

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
class LoadBalancing{
public: 
    static int solveGreedy(vector<int> & jobs,int m){
        if(m<=0){
            return 0;
        }
        int n=jobs.size();
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        vector<int> load(m,0);
        for(int i=0;i<m;i++){
            pq.push({load[i],i});
        }
        for(auto job:jobs){
            int addon=job;
            pii top=pq.top();pq.pop();
            top.first+=addon;
            int index=top.second;
            load[index]+=addon;
            pq.push(top);
        }
        int maxLoad=0;
        for(int i=0;i<m;i++){
            // cout<<"i : "<<i<<" , load => "<<load[i]<<endl;
            maxLoad=max(maxLoad,load[i]);
        }
        return maxLoad;
    }
    static int solveRandom(vector<int> & jobs,int m){
        int n=jobs.size();
        vector<int> load(m,0);
        RandomEngine* rng=new RandomEngine();
        for(auto job:jobs){
            int index=rng->get(m);
            load[index]+=job;
        }
        int maxLoad=0;
        for(int i=0;i<m;i++){
            cout<<i<<" : "<<load[i]<<endl;
            maxLoad=max(maxLoad,load[i]);
        }
        delete rng;
        return maxLoad;
    }
};  
signed main()
{
    int m=3;
    vector<int> jobs={5,4,3,2,6};
    int greedyLoad=LoadBalancing::solveGreedy(jobs,m);
    cout<<"greedy load : "<<greedyLoad<<endl;
    int randomLoad=LoadBalancing::solveRandom(jobs,m);
    cout<<"random load : "<<randomLoad<<endl;
    return 0;
}

