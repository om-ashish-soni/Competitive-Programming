def ncr(n, r):
    p = 1
    k = 1
    if (n - r < r):
        r = n - r
    if (r != 0):
        while (r):
            p *= n
            k *= r
            m = gcd(p, k)
            p //= m
            k //= m
            n -= 1
            r -= 1
    else:
        p = 1
    return p
