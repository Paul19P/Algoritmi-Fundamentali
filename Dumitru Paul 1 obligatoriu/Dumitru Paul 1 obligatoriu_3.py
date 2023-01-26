#folosesc topological sort, si un tracker prin care verific daca exista sau nu un ciclu in graf
#de fiecare data cand se ajunge la un nod terminal sau cand am vizitat toti vecinii nodului respectiv, adaugam nodul la stack
#apoi returnam stack ul invers
class Solution(object):
    def findOrder(self, numCourses, prerequisites):

        self.ciclu = False
        stack = []
        visited = set()
        tracker = set()

        adj = [[] for x in range(numCourses)]
        for a, b in prerequisites:
            adj[b].append(a)

        def dfs(node, visited, stack, tracker):
            visited.add(node)
            tracker.add(node)
            for x in adj[node]:
                if x in tracker:
                    self.ciclu = True
                if x not in visited:
                    dfs(x, visited, stack, tracker)
            tracker.remove(node)
            stack.append(node)

        for i in range(numCourses):
            if i not in visited:
                dfs(i, visited, stack, tracker)
        if self.ciclu == True:
            return []
        return stack[::-1]

a = Solution()
n=4
p=[[1,0],[2,0],[3,1],[3,2]]
print(a.findOrder(n,p))