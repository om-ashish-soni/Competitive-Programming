// problem link : https://practice.geeksforgeeks.org/problems/is-binary-tree-heap/1/
// solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node *buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node *root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current Node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current Node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current Node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


 // } Driver Code Ends
// User Function template for C++

// Structure of node
/*struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

class Solution {
  public:
    int getlevel(struct Node* tree){
        if(!tree) return 0;
        return 1+getlevel(tree->left);
    }
    int getval(struct Node* tree){
        if(!tree) return INT_MIN;
        return tree->data;
    }
    bool ishead(struct Node* tree,vector<bool> & isblocked, int level){
        int levels=isblocked.size();
        if(!tree){
            if(level==levels) return true;
            else if(level==levels-1){
                isblocked[level]=true;
                return true;
            }
            return false;
        }
        if(isblocked[level]) return false;
        if(tree->data<getval(tree->left)) return false;
        if(tree->data<getval(tree->right)) return false;
        return ishead(tree->left,isblocked,level+1)&&ishead(tree->right,isblocked,level+1);
    }
    bool isHeap(struct Node* tree) {
        int n=getlevel(tree);
        if(n<2) return true;
        vector<bool> isblocked(n,false);
        return ishead(tree,isblocked,0);
    }
};

// { Driver Code Starts.

int main() {
    int tc;
    scanf("%d ", &tc);
    while (tc--) {
        string treeString;
        getline(cin, treeString);
        Solution ob;
        Node *root = buildTree(treeString);
        if (ob.isHeap(root))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }

    return 0;
}  // } Driver Code Ends
