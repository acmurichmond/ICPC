# https://open.kattis.com/problems/water
# credit: https://github.com/Dabendorf/INF237-AlgoritmeEngineering/blob/d33f6fae5b23e740f72f5767c6d28ff1a079935c/10-Graphs3/Water.py


from collections import defaultdict, deque
import sys


class Graph:
    edges = defaultdict(lambda: defaultdict(lambda: None))
    R = defaultdict(lambda: defaultdict(lambda: 0))

    def __init__(self, orig_cap, V):
        for k in orig_cap:
            a, b, w = k
            self.edges[a][b] = w
            self.R[a][b] = w
        self.V = V


""" There is a flow network existing, using pumping stations. 
	This means flow can go in both directions in each edge.
	Calculate the maximum flow from node 1 to node 2
	There will be k "improvements" which means that the edge capacities will increase (or start to exist)
	Give out k more numbers being the new network flows after each improvement

	Solution:
	- Straight forward Ford-Fulkerson (Edmonds-Karp) from 1 to 2
	- Difference is that we initialise each edge in both directions and also each residual edge in both
	- Then run the flow network and output the maxflow
	- Each improvement just adds the extra capacity to both the two edges and two residual edges
	- For every improvement, run the maxflow algorithm again (will only run for one bfs?)
	- The new maxflow is the sum of the maxflow from before and the new one
	"""


def main():
    num_stations, num_pipes, num_improvements = list(map(int, sys.stdin.readline().strip().split()))

    # Read original graph into original capacities, every node exists two times as "a" and "b" (bipartite)
    orig_cap = list()
    for _ in range(num_pipes):
        A, B, weight = list(map(int, sys.stdin.readline().strip().split()))
        orig_cap.append((A, B, weight))
        orig_cap.append((B, A, weight))

    V = list(range(1, num_stations + 1))

    graph = Graph(orig_cap, V)
    s = 1
    t = 2

    # Run max-flow
    mflow = maxflow(graph, s, t)
    print(mflow)

    for _ in range(num_improvements):
        A, B, weight = list(map(int, sys.stdin.readline().strip().split()))

        # if edge does not exist before, add it, if not just increase the capacities
        if graph.edges[A][B] != None:
            graph.edges[A][B] += weight
            graph.edges[B][A] += weight
            graph.R[A][B] += weight
            graph.R[B][A] += weight
        else:
            graph.edges[A][B] = weight
            graph.edges[B][A] = weight
            graph.R[A][B] = weight
            graph.R[B][A] = weight

        maxflow_new = maxflow(graph, s, t) + mflow
        mflow = maxflow_new
        print(mflow)


edges = lambda p: zip(p, p[1:])


def bfs(graph, s, t):
    q = deque([s])
    parent = {}
    while q:
        v = q.popleft()
        # for u in graph.V: # !
        for u in graph.R[v]:
            if u in parent:
                continue  # seen it before
            if graph.R[v][u] <= 0:
                continue  # vu saturated
            parent[u] = v
            q.append(u)
            if u == t:
                return create_path(parent, s, t)


def create_path(parent, s, t):
    """ Creates a path from s to t (bfs helper method)"""
    path = [t]
    while t != s:
        t = parent[t]
        path.append(t)
    return tuple(reversed(path))


def maxflow(graph, s, t):
    """ As long as there are paths from s to t existing, increase the flow by the bottleneck
		Then return maximum flow
		The capacities of each edges can be read via the residual graph
	"""
    flow = 0
    P = bfs(graph, s, t)
    while P:
        F = min(graph.R[v][u] for (v, u) in edges(P))
        flow += F
        for i in range(1, len(P)):
            v, u = P[i - 1], P[i]
            graph.R[v][u] -= F
            graph.R[u][v] += F
        P = bfs(graph, s, t)
    return flow


if __name__ == "__main__":
    main()
