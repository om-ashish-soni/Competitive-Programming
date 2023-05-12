/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildtree(int preorder[],int inorder[],int n,int &i){
        if(n<=0 ) return NULL;
        TreeNode* root=new TreeNode(*preorder);
        int *curr=find(inorder,inorder+n,*preorder);
        int temp=i;
        i++;
        root->right=buildtree(preorder+1,curr+1,inorder+n-curr-1,i);
        root->left=buildtree(preorder+i-temp,inorder,curr-inorder,i);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n=inorder.size();
        
        int post[n],in[n];
        for(int i=0;i<n;i++){
            in[i]=inorder[i];
            post[i]=postorder[n-i-1];
        }
        int i=0;
        return buildtree(post,in,n,i);
    }
//         //base condition
//         if(postorder.size()==0){
//             return NULL;
//         }
                
//         //declaration 
//         vector<int> rightPost,rightIn,leftPost,leftIn;
//         int rightLen,leftLen,n=inorder.size();
        
//         //making current root Node && fixing bug
//         TreeNode* root=new TreeNode(*(postorder.end()-1));
//         postorder.pop_back();
//         if(postorder.size()==0){
//             root->left=NULL;
//             root->right=NULL;
//             return root;
//         }
//         //implementation on right subTree
//         int lastNode=*(postorder.end()-1);
//         auto rightStart=find(inorder.begin(),inorder.end(),lastNode);
//         for(auto it=rightStart+1;it!=inorder.end();it++){
//             rightIn.push_back(*it);
//         }
//         rightLen=(inorder.end()-rightStart)-1;
//         auto rightPostStart=postorder.end();
//         while(rightLen--) rightPostStart--;
//         for(auto it=rightPostStart;it!=postorder.end();it++,rightLen++){
//             rightPost.push_back(*it);
//         }
//         while(rightLen--) postorder.pop_back();
//         root->right=buildTree(rightIn,rightPost);
        
        
//         //implementation on left subTree
//         auto leftStart=inorder.begin();
//         for(auto it=leftStart;it!=rightStart;++it){
//             leftIn.push_back(*it);
//         }
//         leftLen=rightStart-inorder.begin();
//         auto leftPostStart=postorder.end();
//         while(leftLen--) leftPostStart--;
//         for(auto it=leftPostStart;it!=postorder.end();it++,leftLen++){
//             leftPost.push_back(*it);
//         }
//         while(leftLen--) postorder.pop_back();
//         root->left=buildTree(leftIn,leftPost);
//         return root;
//     }
};