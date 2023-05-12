#include <bits/stdc++.h>
#define int long long
#define doubel long double

using namespace std;

void print(vector<double> & row){
    cout<<fixed<<setprecision(2);
    for(auto num:row) cout<<num<<" ";cout<<endl;
}
void solve(int t)
{
    int m;
    cin>>m;
    int n;
    cin>>n;
    
    vector<vector<double>> v(m,vector<double>(n));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>v[i][j];
        }
    }
    vector<vector<double>> x_minus_mean(m,vector<double>(n,0.0));
    vector<vector<double>> x_minus_mean_sq(m,vector<double>(n,0.0));
    vector<vector<vector<double>>> co_x_minus_mean(m,vector<vector<double>>(m,vector<double>(n,0.0)));
    vector<vector<double>> variance(m,vector<double>(m,0.0));
    vector<double> mean(m,0.0);

    for(int i=0;i<m;i++){
        vector<double> & row=v[i];
        cout<<"x"<<i+1<<" : ";print(row);
        mean[i]=accumulate(row.begin(),row.end(),0.0)/(1.0*n);
        for(int j=0;j<n;j++){
            x_minus_mean[i][j]=row[j]-mean[i];
        }
    }
    for(int i=0;i<m;i++){
        cout<<"mean of x"<<i+1<<" : "<<mean[i]<<endl;
    }
    for(int i=0;i<m;i++){
        cout<<"x"<<i+1<<"-"<<"m"<<i+1<<" : ";print(x_minus_mean[i]);
        for(int j=0;j<n;j++){
            x_minus_mean_sq[i][j]=x_minus_mean[i][j]*x_minus_mean[i][j];
        }
    }
    for(int i=0;i<m;i++){
        cout<<"(x"<<i+1<<"-"<<"m"<<i+1<<")^2 : ";print(x_minus_mean_sq[i]);
    }
    for(int i=0;i<m;i++){
        for(int j=i;j<m;j++){
            vector<double>& row=co_x_minus_mean[i][j];
            for(int k=0;k<n;k++){
                row[k]=(x_minus_mean[i][k]*x_minus_mean[j][k]);
            }
            variance[i][j]=accumulate(row.begin(),row.end(),0.0)/(1.0*n);
            if(i != j){
                co_x_minus_mean[j][i]=co_x_minus_mean[i][j];
                variance[j][i]=variance[i][j];
            }
            cout<<"(x"<<i+1<<"-m"<<i+1<<")*(x"<<j+1<<"-m"<<j+1<<") : "<<endl;
            print(co_x_minus_mean[i][j]);
        }
    }
    cout<<"covariance matrix : "<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            cout<<variance[i][j]<<" ";
        }
        cout<<endl;
    }


    
}


signed main()
{
    int t = 1;
    // cin >> t; // testcase
    while (t--)
    {
        solve(t);
    }
    return 0;
}