#algoritmul lui dijkstra
class Solution:
    def maxProbability(self, n: int, edges: List[List[int]], succProb: List[float], start: int, end: int) -> float:
        d = [0.0] * n
        d[start] = 1.0
        graph = collections.defaultdict(list)
        heap = []
        for (u, v), p in zip(edges, succProb):
            graph[u].append((v, p))
            graph[v].append((u, p))
        heapq.heappush(heap, (-1.0, start))
        while len(heap) > 0:
            p, nod = heapq.heappop(heap)
            p = -p
            if nod == end:
                return p
            if d[nod] > p:
                continue
            for v, prob in graph[nod]:
                if d[v] < p * prob:
                    d[v] = p * prob
                    heapq.heappush(heap, (-(p * prob), v))
        return 0


