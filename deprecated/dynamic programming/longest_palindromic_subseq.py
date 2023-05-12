# problem desc:
# Recall that a subsequence of a string S is obtained by deleting some characters from S and without changing the order of the remaining characters. And a palindrome is a word that equals its reverse. Here are some examples of palindromes: "malayalam", "gag", "appa", "amma".

# Given a string S consists of only lowercase characters. Find the length of the longest subsequence which is a palindrome.

# Input
# The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
# Each testcase contains a single line of input a string S
# Output
# For each test case, output in a single line the answer to the problem - the longest subsequence which is a palindrome.
# Constraints
# 1≤T≤10
# 1≤|S|≤1000
# Example Input
# 2
# abefbca
# abc
# Example Output
# 5
# 1
# Explanation
# Example case 1: One of the longest palindromic subsequences is "abeba".
# solution : below code
import sys,io,os,copy,heapq,bisect
from math import log2,ceil,gcd,floor
from sys import stdin,stdout
sys.setrecursionlimit(10**9)
# isIo=True
isIo=False

if isIo:
    stdin = open('input.txt', 'r')
    stdout = open('output.txt', 'w')
input=stdin.readline
def printend(*argv):
    output=""
    for arg in argv: output+=str(arg)+" "
    stdout.write(output)
def print(*argv):
    output=""
    for arg in argv: output+=str(arg)+" "
    stdout.write(output+"\n")

def isSumPossible(lst,index,sm,rem):
    if sm<0 or rem<sm or index>=len(lst): return False
    if sm==0: return True
    res=isSumPossible(lst,index+1,sm-lst[index],rem-lst[index]) or isSumPossible(lst,index+1,sm,rem-lst[index])
    return res
# for _ in range(1):
memo={}
memo[(1,2)]=3

def getsubseqpal(s,l,r):
    if l>r: return 0
    if l==r: return 1
    if (l,r) in memo:return memo[(l,r)]
    length=0
    if s[l]==s[r]: length=2+getsubseqpal(s,l+1,r-1)
    else:length=max(getsubseqpal(s,l,r-1),getsubseqpal(s,l+1,r))
    memo[(l,r)]=length
    return length
    pass
for _ in range(int(input())):
    memo.clear()
    s=input()
    n=len(s)-1
    s=s[0:n]
    length=getsubseqpal(s,0,n-1)
    print(length)
