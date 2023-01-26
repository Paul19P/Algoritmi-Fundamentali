from collections import defaultdict


# Folosim algoritmul lui Hierholzer
# Complexitate O(n+m)
# n-numar varfuri
# m-numar arce
class Solution:
    def validArrangement(self, pairs):
        adj = defaultdict(list)
        d = defaultdict(int)
        # calculam gradele fiecarui varf si pornim de la cel care are gradul unu,adica cel terminal
        for pair in pairs:
            adj[pair[0]].append(pair[1])
            d[pair[0]] += 1
            d[pair[1]] -= 1
        start = pairs[0][0]
        for u in adj.keys():
            if d[u] == 1:
                start = u
                break
        ans = []

        # rulam un dfs pentru a afla drumul de la nodul start la celalalt nod terminal
        def dfs(u):
            while adj[u]:
                v = adj[u].pop()
                dfs(v)
                ans.append([u, v])

        dfs(start)
        return ans[::-1]


pairs = [[5,1],[4,5],[11,9],[9,4]]
s=Solution()
print(s.validArrangement(pairs))