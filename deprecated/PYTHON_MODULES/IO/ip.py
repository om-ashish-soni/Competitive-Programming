import sys
import copy
import math
isIo=True

sys.setrecursionlimit(10**6)
if(isIo):
	sys.stdin = open('input.txt', 'r')
	sys.stdout = open('output.txt', 'w')
isTakeTestCase=False
def scanIntList():
	return map(int,input().split())
def printList(lst):
	for elem in lst:
		print(elem,end=" ")
	print()

