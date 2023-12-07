"""https://ualberta.kattis.com/sessions/v6p28m/problems/copsandrobbers

Approach:
- Construct a network flow graph with each vertex being split into 2 and edge between
them representing cost of the vertex.
- The size of the graph will be n * m * 2 + 2, with 2 added vertices of s and t.
- Then, we simple need the minimum cut of this graph, i.e. the vertices where we need
to put barricades to cut flow from s and t.
By max flow min cut therem, this is simply the max flow of the graph.
"""

import sys

from numbers import Number
from copy import deepcopy
from typing import Tuple

INF = float('inf')


class MaxFlow:
    def __init__(self, V: int):
        """
        Creates a new instance of the MaxFlow class. The general way you'll
        want to use this library is to create a new instance of the class,
        add edges, then call the `edmonds_karp` or `dinic` methods.
        While the library does support floats, be aware that it is not advised
        to use due to the potential for floating point errors, meaning small
        amounts of flow may be sent many times.
        Arguments:
            V: The number of vertices in the graph.
        Example:
            # >>> mf = MaxFlow(3)
            # >>> mf.add_edge(0, 1, 3)
            # >>> mf.add_edge(0, 2, 3)
            # >>> mf.add_edge(1, 2, 3)
            # >>> mf.dinic(0, 2)  # or mf.edmonds_karp(0, 2)
            6
        """
        self.V = V
        self.EL = []
        self.AL = [list() for _ in range(self.V)]
        self.d = []
        self.last = []
        self.p = []
        self.has_been_run = False

    def BFS(self, s: int, t: int) -> bool:
        self.d = [-1] * self.V
        self.d[s] = 0
        self.p = [[-1, -1] for _ in range(self.V)]
        q = [s]
        while len(q) != 0:
            u = q[0]
            q.pop(0)
            if u == t:
                break
            for idx in self.AL[u]:
                v, cap, flow = self.EL[idx]
                if cap - flow > 0 and self.d[v] == -1:
                    self.d[v] = self.d[u] + 1
                    q.append(v)
                    self.p[v] = [u, idx]
        return self.d[t] != -1

    def send_one_flow(self, s: int, t: int, f: Number = INF) -> Number:
        if s == t:
            return f
        u, idx = self.p[t]
        _, cap, flow = self.EL[idx]
        pushed = self.send_one_flow(s, u, min(f, cap - flow))
        flow += pushed
        self.EL[idx][2] = flow
        self.EL[idx ^ 1][2] -= pushed
        return pushed

    def DFS(self, u: int, t: int, f: Number = INF) -> Number:
        if u == t or f == 0:
            return f
        for i in range(self.last[u], len(self.AL[u])):
            self.last[u] = i
            v, cap, flow = self.EL[self.AL[u][i]]
            if self.d[v] != self.d[u] + 1:
                continue
            pushed = self.DFS(v, t, min(f, cap - flow))
            if pushed != 0:
                flow += pushed
                self.EL[self.AL[u][i]][2] = flow
                self.EL[self.AL[u][i] ^ 1][2] -= pushed
                return pushed
        return 0

    def add_edge(self, u: int, v: int, capacity: Number,
                 directed: bool = True) -> None:
        """
        Adds an edge from `u` to `v` with capacity `w`. By default, the edge is
        directed, i.e. `u`->`v`. You can set `directed = False` to add it
        as an undirected edge `u`<->`v`.
        Arguments:
            `u`: The first vertex.
            `v`: The second vertex.
            `capacity`: The capacity of the edge.
            `directed`: Whether the edge is directed. True by default.
        Example:
            # >>> mf = MaxFlow(3)
            # >>> mf.add_edge(0, 1, 3)
            # >>> mf.add_edge(2, 1, 3)
        """
        if u == v:
            return
        self.EL.append([v, capacity, 0])
        self.AL[u].append(len(self.EL) - 1)
        self.EL.append([u, 0 if directed else capacity, 0])
        self.AL[v].append(len(self.EL) - 1)

    def assert_has_not_already_been_run(self):
        if self.has_been_run:
            msg = ('Rerunning a max flow algorithm on the same graph will '
                   + 'result in incorrect behaviour. Please use .copy() '
                   + 'before you run any max flow algorithm if you need to '
                   + 'run multiple iterations')
            raise Exception(msg)

        self.has_been_run = True

    def edmonds_karp(self, s: int, t: int) -> Number:
        """
        Returns the max flow obtained by running Edmons-Karp algorithm.
        Modifies the graph in place.
        Arguments:
            `s`: The source vertex.
            `t`: The sink vertex.
        Returns:
            The max flow.
        """
        self.assert_has_not_already_been_run()

        mf = 0
        while self.BFS(s, t):
            f = self.send_one_flow(s, t)
            if f == 0:
                break
            mf += f
        return mf

    def dinic(self, s: int, t: int) -> Number:
        """
        Returns the max flow obtained by running Dinic's algorithm.
        Modifies the graph in place.
        Arguments:
            `s`: The source vertex.
            `t`: The sink vertex.
        Returns:
            The max flow.
        """
        self.assert_has_not_already_been_run()

        mf = 0
        while self.BFS(s, t):
            self.last = [0] * self.V
            f = self.DFS(s, t)
            while f != 0:
                mf += f
                f = self.DFS(s, t)
        return mf

    def copy(self) -> 'MaxFlow':
        """
        Returns a deep copy of the current instance. This is convenient for
        problems where you need to run MaxFlow multiple times on slightly
        different graphs, since the instance is destroyed after each max flow
        run.
        Example:
            # >>> mf = MaxFlow(4)
            # >>> mf.add_edge(0, 1, 3)
            # >>> mf.add_edge(1, 2, 3)
            # >>> for c in range(1, 4):
            # >>>     mf_copy = mf.copy()
            # >>>     mf_copy.add_edge(2, 3, c)
            # >>>     res = mf_copy.dinic(0, 3)  # Will not modify mf
        """
        return deepcopy(self)

    def __repr__(self) -> str:
        el = self.EL[:10] + ['...'] if len(self.EL) > 10 else self.EL
        al = self.AL[:10] + ['...'] if len(self.AL) > 10 else self.AL
        el = ', '.join(map(str, el))
        al = ', '.join(map(str, al))
        return f'MaxFlow(V={self.V}, EL=[{el}], AL=[{al}])'


def get_vertex_ids(row, col, n, m) -> Tuple[int, int]:
    id1 = row * n + col
    id2 = id1 + (n * m)
    return (id1, id2)


def is_coord_in_board(row, col, n, m) -> bool:
    if row < 0 or row >= m:
        return False
    if col < 0 or col >= n:
        return False
    return True


def cops_and_robbers(n, m, board, barricade_costs) -> None:
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    num_vertices = (n * m * 2) + 2
    s = num_vertices - 1  # id for s vertex
    t = num_vertices - 2  # id for s vertex
    mf = MaxFlow(num_vertices)

    for i in range(m):
        for j in range(n):
            id1, id2 = get_vertex_ids(i, j, n, m)  # we split a vertex into two

            if board[i][j] == 'B':
                mf.add_edge(s, id2, INF)  # s is connected only to the B vertex
            elif board[i][j] == '.':
                mf.add_edge(id1, id2, INF)
            else:
                cost = barricade_costs[ord(board[i][j]) - ord('a')]
                mf.add_edge(id1, id2, cost)

            for ix, iy in directions:
                x_new = i + ix
                y_new = j + iy

                if is_coord_in_board(x_new, y_new, n, m):
                    adjacent_neighbor_id, _ = get_vertex_ids(x_new, y_new, n, m)
                    mf.add_edge(id2, adjacent_neighbor_id, INF)
                else:
                    mf.add_edge(id2, t, INF)

    max_flow = mf.dinic(s, t)
    if max_flow >= INF:
        print(-1)
    else:
        print(max_flow)


def water():
    n, p, k = map(int, input().split())
    mf = MaxFlow(n)
    dic = {}
    for _ in range(p):
        a, b, c = map(int, input().split())
        dic[(a, b)] = c
        mf.add_edge(a-1, b-1, c, directed=False)
    # print(mf.EL)
    mf_c = mf.copy()
    org = mf_c.edmonds_karp(0, 1)
    print(org)

    for _ in range(k):
        mf = MaxFlow(n)
        a, b, c = map(int, input().split())
        if (a, b) in dic:
            dic[(a, b)] += c
            # mf.add_edge(a-1, b-1, dic[(a, b)])
        elif (b, a) in dic:
            dic[(b, a)] += c
            # mf.add_edge(b-1, a-1, dic[(b, a)])
        else:
            dic[(a, b)] = c
            # mf.add_edge(a-1, b-1, c, directed=False)

        for i in dic:
            mf.add_edge(i[0] - 1, i[1] - 1, dic[i], directed=False)
        max_flow = mf.edmonds_karp(0, 1)
        print(max_flow)


def main():
    input_lines = sys.stdin.read().splitlines()
    n, m, c = list(map(int, input_lines[0].split()))
    board = input_lines[1: -1]
    barricade_costs = list(map(int, input_lines[-1].split()))
    cops_and_robbers(n, m, board, barricade_costs)


if __name__ == '__main__':
    main()