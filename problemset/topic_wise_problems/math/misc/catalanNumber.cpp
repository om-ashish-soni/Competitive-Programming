// Problem link : https://practice.geeksforgeeks.org/problems/nth-catalan-number0817/1
// Solution : below code

// { Driver Code Starts
//Initial template for C++

#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;  // https://www.geeksforgeeks.org/factorial-large-number-using-boost-multiprecision-library/
using namespace std;


 // } Driver Code Ends
//User function template for C++

vector<cpp_int> catalan{vector<cpp_int>(110,0)};

class Solution
{
    public:
    //Function to find the nth catalan number.
    cpp_int findCatalan(int n) 
    {
        if(n<2) return 1;
        if(catalan[n] != 0) return catalan[n];
        for(int i=0;i<n;i++){
            catalan[n]+=findCatalan(i)*findCatalan(n-i-1);
        }
        return catalan[n];
        //code here
    }
};

// { Driver Code Starts.

int main() 
{
    //taking count of testcases
	int t;
	cin>>t;
	while(t--) {
	    
	    //taking nth number
	    int n;
	    cin>>n;
	    Solution obj;
	    //calling function findCatalan function
	    cout<< obj.findCatalan(n) <<"\n";    
	}
	return 0;
}  // } Driver Code Ends
