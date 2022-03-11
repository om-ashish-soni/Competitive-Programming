# O(sqrt(n))
def isPrime(n):
    if n==1: return False
    p=2
    while(True):
        if n>=int(p*p):
            if n%p==0:return False
            else: p+=1
        else:return True
    return True
