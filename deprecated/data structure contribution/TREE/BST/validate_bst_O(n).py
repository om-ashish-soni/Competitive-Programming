# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/94/trees/625/

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
inf=int(10**20)
def validate(root):
    
    left=[-inf,-inf]
    right=[inf,inf]
    curr=[root.val,root.val]
    if root.left:
        left=validate(root.left)
        if left==False : return False
        if left[1]>=root.val: return False
        curr[0]=min(curr[0],left[0])
    if root.right:
        
        right=validate(root.right)
        if right==False: return False
        if right[0]<=root.val: return False
        curr[1]=max(curr[1],right[1])
    # print(root.val,curr)
    return curr

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        if validate(root)==False: return False
        return True
