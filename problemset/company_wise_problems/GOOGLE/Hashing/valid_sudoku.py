# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/769/
# companies : GOOGLE & AMAZON

def check(board,r,c):
    memo={}
    for i in range(r,r+3):
        for j in range(c,c+3):
            if board[i][j] != 0:
                if board[i][j] in memo: 
                    print(r,c,memo,i,j,"at : ",board[i][j])
                    return False
                memo[board[i][j]]=True
    return True
class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        horz=[[0,0,0,0,0,0,0,0,0,0] for _ in range(len(board))]
        vert=[[0,0,0,0,0,0,0,0,0,0] for _ in range(len(board))]
        for i in range(len(board)):
            for j in range(len(board)):
                if board[i][j] != ".":
                    board[i][j]=int(board[i][j])
                    horz[i][board[i][j]]+=1
                    vert[j][board[i][j]]+=1
                else:board[i][j]=0
        for i in range(len(board)):
            for num in range(1,10):
                if horz[i][num]>1: return False
                if vert[i][num]>1: return False
        for i in range(0,9,3):
            for j in range(0,9,3):
                if False==check(board,i,j): return False
        return True
        
            
