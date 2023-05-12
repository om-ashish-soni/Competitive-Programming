/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    void connect(Node* root,vector<Node*> &v,int level=0){
        if(!root) return;
        if(v.size()>level){
            v[level]->next=root;
            v[level]=root;
        }else{
            v.push_back(root);
        }
        connect(root->left,v,level+1);
        connect(root->right,v,1+level);
        return;
    }
    Node* connect(Node* root) {
        if(!root)  return root;
        vector<Node*> nodes;
        connect(root,nodes);
        return root;
    }
};