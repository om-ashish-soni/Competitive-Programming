// C++ implementation of above approach
#include <bits/stdc++.h>
#include <string>
using namespace std;
 
// Function to remove duplicates
string removeDuplicatesFromString(string str)
{
 
    // keeps track of visited characters
    int counter = 0;
 
    int i = 0;
    int size = str.size();
 
    // gets character value
    int x;
 
    // keeps track of length of resultant string
    int length = 0;
 
    while (i < size) {
        x = str[i] - 97;
 
        // check if Xth bit of counter is unset
        if ((counter & (1 << x)) == 0) {
 
            str[length] = 'a' + x;
 
            // mark current character as visited
            counter = counter | (1 << x);
 
            length++;
        }
        i++;
    }
 
    return str.substr(0, length);
}
 
// Driver code
int main()
{
    string str = "geeksforgeeks";
    cout << removeDuplicatesFromString(str);
    return 0;
}