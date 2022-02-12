// Problem link : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
// Solution : below code 

class Solution {
public:
    // disjointSet
    class disjointSet{

        public:
        // unordered_map<int,int> ump;
        vector<int> ump;
        disjointSet(){}
        disjointSet(vector<int>& arr){
            ump.resize(arr.size()+1);
            for(auto num:arr) ump[num]=-1;
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
        bool preferedUnion(int u,int v){
            int uroot=findSet(u);
            int vroot=findSet(v);
            if(uroot == vroot) return false;
            int uchild=ump[uroot];
            int vchild=ump[vroot];
            int totalChild=uchild+vchild;
            ump[vroot]=uroot;
            ump[uroot]=totalChild;
            return true;
        }
        void print(){
            // for(auto &pr:ump){
            //     cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
            // }
        }
    };
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(),events.end(),[](auto &a,auto &b){
            if(a[1]-a[0] == b[1]-b[0]){
                return a[0]<b[0];
            }
            return (a[1]-a[0] < b[1]-b[0]) ; 
        });
        
        int n=events.size();
        int m=0;
        for(int i=0;i<n;i++ ){
            m=max(m,events[i][1]);
        }
        vector<int> vcont(m+1);
        vector<bool> isDone(m+1,false);
        vector<pair<int,int>> v(m+1);
        for(int i=0;i<m+1;i++) vcont[i]=i+1;
        disjointSet ds=*new disjointSet(vcont);
        int ctr=0;
        for(int i=0;i<n;i++){
            int start=events[i][0];
            int end=events[i][1];
            int q=ds.findSet(start);
            if(q<=end){
                v[q]={start,end};
                ds.preferedUnion(q+1,q);
                ctr++;
            }else{
                for(int j=start;j<=end;j++){
                    int found=ds.findSet(v[j].first);
                    if(found<=v[j].second){
                        v[found]=v[j];
                        ds.preferedUnion(found+1,found);
                        v[q]={start,end};
                        ds.preferedUnion(q+1,q);
                        ctr++;
                        break;
                    }
                }
            }
        }
        // ds.print();
        return ctr;
    }
};
