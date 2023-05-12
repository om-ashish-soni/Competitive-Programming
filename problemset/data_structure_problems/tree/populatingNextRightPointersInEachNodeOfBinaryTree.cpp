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
    void collectNodes(Node* root,vector<vector<Node*>> &vv,int level=0){
        if(!root) return;
        if(vv.size() > level){
            vv[level].push_back(root);
        }else{
            vector<Node*> thisLevel;
            thisLevel.push_back(root);
            vv.push_back(thisLevel);
        }
        collectNodes(root->left,vv,1+level);
        collectNodes(root->right,vv,1+level);
        return ;
    }
    Node* connect(Node* root) {
        if(!root) return NULL;
        vector<vector<Node*>> levelWiseNodes;
        collectNodes(root,levelWiseNodes);
        for(int i=0;i<levelWiseNodes.size();i++){
            int n=levelWiseNodes[i].size();
            for(int j=0;j<n-1;j++){
                levelWiseNodes[i][j]->next=levelWiseNodes[i][j+1];
            }
            levelWiseNodes[i][n-1]->next=NULL;
        }
        return levelWiseNodes[0][0];
    }
};