#O(K*E)
#Am folosit Algoritmul Bellman-Ford
class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        dist=[float('inf')]*n
        dist[src]=0
        for i in range(k+1):
            cdist=dist.copy()
            for u,v,p in flights:
                if dist[u]==float('inf'):
                    continue
                if dist[u]+p<cdist[v]:
                    cdist[v]=dist[u]+p
            dist=cdist
        if dist[dst]==float('inf'):
            return -1
        else:
            return dist[dst]