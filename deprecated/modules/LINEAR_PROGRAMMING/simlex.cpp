#include<bits/stdc++.h>
using namespace std;
class Simplex{
    vector<double> coef;
    vector<vector<double> > mat;
    vector<double> rhs,basic;
    int equations,variables;
    public:
    Simplex(vector<double>& coef,vector<vector<double> > & mat,vector<double> & rhs,vector<double>& basic){
        this->coef=coef;
        this->mat=mat;
        this->rhs=rhs;
        this->basic=basic;
        this->variables=coef.size();
        this->equations=mat.size();
    }    
    void solve(){
        cout<<"in simplex solve"<<endl;
        cout<<"basics : "<<endl;
        for(int i=0;i<equations;i++) cout<<basic[i]<<" ";cout<<endl;

        vector<double> zj(variables,0);
        vector<double> cjzj(variables,0);
        vector<double> theta(equations,0);
        for(int i=0;i<variables;i++){
            for(int j=0;j<equations;j++){
                int index=basic[j];
                //cout<<"index : "<<index<<endl;
                zj[i]+=coef[index]*mat[j][i];
            }
            //cout<<zj[i]<<" ";
        }
        //cout<<endl;
        for(int i=0;i<variables;i++){
            cjzj[i]=coef[i]-zj[i];
        }

        //base case to terminate
        bool shouldTerminate=true;
        for(int i=0;i<variables;i++){
            if(cjzj[i]>0){
                shouldTerminate=false;
                break;
            }
        }
        if(shouldTerminate){
            cout<<"terminating now ----------------"<<endl;
            cout<<"basics : "<<endl;
            for(int i=0;i<equations;i++) cout<<basic[i]<<" ";cout<<endl;
            for(int i=0;i<10;i++) cout<<"+++++";cout<<endl;
            cout<<"SIMPLEX TABULAR SOLUTION : "<<endl;
            double objective=0;
            for(int i=0;i<equations;i++){
                int index=basic[i];
                cout<<"x"<<index+1<<" : "<<rhs[index]<<endl;
                objective+=(coef[index]*rhs[i]);
            }
            cout<<"OBJECTIVE VALUE : "<<objective<<endl;
            for(int i=0;i<10;i++) cout<<"+++++";cout<<endl;
            return;
        }
        int taken=0;
        int removal=0;
        for(int i=1;i<variables;i++){
            if(cjzj[i]>cjzj[taken]){
                taken=i;
            }
        }
        for(int i=0;i<equations;i++){
            theta[i]=rhs[i]/mat[i][taken];
            cout<<theta[i]<<" ";
        }
        cout<<endl;
        for(int i=1;i<equations;i++){
            if(theta[removal]>theta[i]){
                removal=i;
            }
        }
        cout<<"taken : "<<taken<<endl;
        cout<<"removal : "<<removal<<endl;

        basic[removal]=taken;

        int row=removal;
        int col=taken;
        double pivot=mat[row][col];
        cout<<"row : "<<row<<" , col : "<<col<<endl;
        cout<<"pivot : "<<pivot<<endl;
        //resolving row of taken
        
        vector<double> match_row=mat[row];
        vector<double> match_col(equations,0);
        for(int i=0;i<equations;i++) match_col[i]=mat[i][col];
        for(int i=0;i<equations;i++){
            if(i==row) continue;
            for(int j=0;j<variables;j++){
              double cor_row=match_row[j];
              double cor_col=match_col[i];
              double sub=(cor_row*cor_col)/pivot;
              //cout<<i<<" , "<<j<<" : "<<endl;
              //cout<<"\t"<<cor_row<<" , "<<cor_col<<endl;
              mat[i][j]-=sub;
              
            }
        }
        for(int i=0;i<variables;i++){
            mat[row][i]/=pivot;
        }
        vector<double> match_rhs=rhs;    
        for(int i=0;i<equations;i++){
            if(i==row) continue;            
            double cor_row=match_col[i];
            double cor_col=match_rhs[row];
            double sub=(cor_row*cor_col)/pivot;
            rhs[i]-=sub;    
        }
        rhs[row]/=pivot;

        cout<<"rhs : "<<endl;
        for(int i=0;i<equations;i++) cout<<rhs[i]<<" ";cout<<endl;
        for(int i=0;i<equations;i++){
            for(int j=0;j<variables;j++){
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
        //cout<<"calling again ---"<<endl;
        
        this->solve();
    }
};

int main(){
    cout<<"----------- simplex tablular ------------"<<endl;
    int eqautions=2;
    int variables=4;
    vector<double> coef(4);
    coef[0]=10;
    coef[1]=9;
    coef[2]=0;
    coef[3]=0;
    //{3,4,0,0};
    vector<vector<double> > mat(2,vector<double>(4));
    mat[0][0]=3;
    mat[0][1]=3;
    mat[0][2]=1;
    mat[0][3]=0;
    mat[1][0]=4;
    mat[1][1]=3;
    mat[1][2]=0;
    mat[1][3]=1;

    vector<double> rhs(2);
    rhs[0]=21;
    rhs[1]=24;

    vector<double> basic(2);
    basic[0]=2;
    basic[1]=3;

    Simplex *smp=new Simplex(coef,mat,rhs,basic);
    smp->solve();
    delete smp;    
    return 0;
}
