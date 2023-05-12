// problem link : https://binarysearch.com/problems/Subtree
// solution : below code

/**
 * class Tree {
 *     public:
 *         int val;
 *         Tree *left;
 *         Tree *right;
 * };
 */
bool compare(Tree* root,Tree* target){
    if(!root && !target) return true;
    if(!root || !target) return false;
    if(root->val != target->val) return false;
    return compare(root->left,target->left) && compare(root->right,target->right);
}
bool traverse(Tree* root,Tree* target){
    if(!root) return false;
    if(root->val==target->val){
        bool res=compare(root,target);
        if(res) return true;
    }
    return traverse(root->left,target) || traverse(root->right,target);

}
bool solve(Tree* root, Tree* target) {
    if(!target) return true;
    return traverse(root,target);
}
