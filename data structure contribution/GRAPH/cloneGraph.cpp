/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node,unordered_map<int,bool> &visited,unordered_map<int,Node*> &ump) {
        Node* cloneNode=new Node(node->val);
        ump[cloneNode->val]=cloneNode;
        visited[cloneNode->val]=true;
        for(auto elem:node->neighbors){
            if(!visited[elem->val]) cloneNode->neighbors.push_back(cloneGraph(elem,visited,ump));
            else{
                cloneNode->neighbors.push_back(ump[elem->val]);
            }
            visited[elem->val]=true;
        }
        return cloneNode;
    }
    Node* cloneGraph(Node* node){
        if(!node) return NULL;
        unordered_map<int,bool> visited;
        unordered_map<int,Node*> ump;
        return cloneGraph(node,visited,ump);
    }
};