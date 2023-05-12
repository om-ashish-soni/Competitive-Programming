mod = int(1e9+7)

def modAdd(x, y, mod):
    return (x+y) % mod

def modMul(x, y, mod):
    return (x*y) % mod

def modSub(x, y, mod):
    return (x-y) % mod

def modDiv(x, y, mod):
    inv = pow(y, mod-2, mod)
    return (x * inv) % mod

def dfs(start, parent, graph, dp, score1):
    for node in graph[start]:
        if node == parent:
            continue
        child_score = dfs(node, start, graph, dp, score1)
        to_add = modAdd(child_score, 2, mod)
        dp[start].append(to_add)
    for num in dp[start]:
        score1[start] = modMul(score1[start], num, mod)
    score1[start] = modSub(score1[start], 1, mod)
    return score1[start]

def dfs2(start, parent, graph, dp, score1):
    if parent != -1:
        parent_score = score1[parent]
        numer = modAdd(score1[parent], 1, mod)
        denom = modAdd(score1[start], 2, mod)
        div = modDiv(numer, denom, mod)
        to_add = modAdd(div, 1, mod)
        dp[start].append(to_add)
        new_score = 1
        for num in dp[start]:
            new_score = modMul(new_score, num, mod)
        score1[start] = modSub(new_score, 1, mod)
    for node in graph[start]:
        if node == parent:
            continue
        dfs2(node, start, graph, dp, score1)

def solve():
    n = int(input())
    graph = [[] for _ in range(n)]
    dp = [[] for _ in range(n)]
    score1 = [1] * n
    edges = list(map(int, input().split()))
    for i in range(n-1):
        edges[i] -= 1
        graph[i+1].append(edges[i])
        graph[edges[i]].append(i+1)
    dfs(0, -1, graph, dp, score1)
    dfs2(0, -1, graph, dp, score1)
    for i in range(n):
        score1[i] = modAdd(score1[i], 1, mod)
    for score in score1:print(score,end=" ")
    print()

solve()
