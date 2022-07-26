#include <bits/stdc++.h>
using namespace std;
// disjointSet
class disjointSet{
    vector<int> ump;
    public:
    vector<int>& getUmp(){
    	return ump;
    }
    disjointSet(int n){
        ump.assign(n+1,-1);
    }
    int findSet(int u){
        // cout<<"in findSet "<<u<<endl;
        int r=u;
        while(ump[r]>=0){
            r=ump[r];
        }
        while(u!=r){
            int par=ump[u];
            ump[u]=r;
            u=par;
        }
        return r;
    }
    bool setUnion(int u,int v){
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot=findSet(u);
        int vroot=findSet(v);
        if(uroot == vroot) return false;
        int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        
        if(uchild>vchild){
	        ump[uroot]=vroot;
	        ump[vroot]=totalChild;
        }else{
	        ump[vroot]=uroot;
	        ump[uroot]=totalChild;
        }
        return true;
    }
    bool prefered_union(int v,int u){
    	int uroot=findSet(u);
    	int vroot=findSet(v);
    	if(uroot==vroot) return false;
    	int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        ump[uroot]=vroot;
        ump[vroot]=totalChild;
        return true;
    }

    // void giveConnectedComps(vector<vector<int>>& comps){
    // 	for(auto &pr:ump){
    // 		if(pr.first==0) continue;
    // 		if(pr.second > 0){
    // 			comps[pr.second].push_back(pr.first);
    // 		}else{
    // 			comps[pr.first].push_back(pr.first);
    // 		}
    // 	}
    // 	return;
    // }
    // void print(){
    //     for(auto &pr:ump){
    //         cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
    //     }
    // }
};

using namespace std;
int get_random(int n){
    return rand()%n;
}
int main() {
    srand(time(0));
    int n=4;
        
    int iterations=100*(n)*(n-1);
    int min_cut=INT_MAX;
    while(iterations--){
        // cout<<"iterations : "<<iterations<<endl;
        vector<pair<int,int>> edges={{1,2},{1,3},{1,4},{2,4},{3,4}};
        vector<vector<int>> v(n+1,vector<int>(n+1,0));
        for(auto &pr:edges){
            v[pr.first][pr.second]++;
            v[pr.second][pr.first]++;
        }
        disjointSet *ds=new disjointSet(n+1);
        int k=0;
        int rem=n;
        while(rem>2){
            // cout<<" k : "<<++k<<endl;
            int sz=edges.size();
            int index=get_random(sz);
            pair<int,int> edge=edges[index];
            // cout<<"index : "<<index<<endl;
            bool shouldTake=true;
            if(edge.first != ds->findSet(edge.first) || edge.second != ds->findSet(edge.second)){
                shouldTake=false;
            }
            if(shouldTake){
                int first=min(edge.first,edge.second);
                int second=max(edge.first,edge.second);
                // cout<<"edge : "<<"{"<<edge.first<<","<<edge.second<<"}"<<endl;
                bool isDifferent=ds->prefered_union(first,second);
                if(isDifferent){
                    rem--;
                    // cout<<"chosen : "<<first<<" "<<second<<endl;    
                    v[first][second]=0;
                    v[second][first]=0;
                    for(int j=1;j<=n;j++){
                        v[first][j]+=v[second][j];
                        v[j][first]+=v[second][j];
                        v[second][j]=0;
                        v[j][second]=0;
                    }
                }
            }
            swap(edges[index],edges[sz-1]);
            edges.pop_back();
        }
        int cut=0;
        for(int i=1;i<=n;i++){
            // cout<<"i : "<<i<<" , root : "<<ds->findSet(i)<<endl;
            for(int j=1;j<=n;j++){
                // cout<<v[i][j]<<" ";
                cut+=v[i][j];
            }
            // cout<<endl;
        }
        cut/=2;
        min_cut=min(cut,min_cut);
        // cout<<"cut : "<<cut<<endl;
        delete ds;
    }
    cout<<"min cut : "<<min_cut<<endl;
        
    return 0;
}
