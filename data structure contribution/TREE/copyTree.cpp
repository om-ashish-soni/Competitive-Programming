TreeNode* copyTree(TreeNode *root,TreeNode *newTree=NULL){
    if(NULL == root) return root;
    newTree=(TreeNode *)malloc(sizeof(TreeNode));
    newTree->val=root->val;
    newTree->left=copyTree(root->left,newTree->left);
    newTree->right=copyTree(root->right,newTree->right);
    return newTree;
}