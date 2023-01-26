#Algoritmul lui Prim
class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        n =len(points)
        adj={i:[] for i in range(n)}
        for i in range(n-1):
            x1,y1=points[i]
            for j in range(i+1,n):
                x2,y2=points[j]
                d=abs(x1-x2)+abs(y1-y2)
                adj[i].append([d,j])
                adj[j].append([d,i])
        cost_total=0
        visited=set()
        heap=[[0,0]]
        while len(visited)<n:
            cost,nod=heapq.heappop(heap)
            if nod in visited:
                continue
            cost_total+=cost
            visited.add(nod)
            for cost,u in adj[nod]:
                if u not in visited:
                    heapq.heappush(heap,[cost,u])
        return cost_total