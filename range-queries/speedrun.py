class Interval:
    def __init__(self, start, end):
        self.start = start
        self.end = end

class Node:
    def __init__(self, interval):
        self.interval = interval
        self.max = interval.end
        self.left = None
        self.right = None

class IntervalTree:
    def __init__(self):
        self.root = None

    def insert(self, root, interval):
        if root is None:
            return Node(interval)

        if interval.start < root.interval.start:
            root.left = self.insert(root.left, interval)
        else:
            root.right = self.insert(root.right, interval)

        root.max = max(root.max, interval.end)
        return root

    def overlap_search(self, root, interval):
        if root is None:
            return False

        if self.do_overlap(root.interval, interval):
            return True

        if root.left is not None and root.left.max >= interval.start:
            if self.overlap_search(root.left, interval):
                return True

        return self.overlap_search(root.right, interval)

    @staticmethod
    def do_overlap(interval1, interval2):
        return (interval1.start < interval2.end) and (interval2.start < interval1.end)

def can_complete_tasks(T, tasks):
    tree = IntervalTree()
    tasks.sort(key=lambda x: x[1])  # Sort tasks by end time

    count = 0
    for start, end in tasks:
        if not tree.overlap_search(tree.root, Interval(start, end)):
            tree.root = tree.insert(tree.root, Interval(start, end))
            count += 1
            if count >= T:
                return "YES"

    return "NO"


def main():
    G, N = [int(i) for i in input().split(" ")]
    task = []
    for _ in range(N):
        l, r = [int(i) for i in input().split(" ")]
        task.append((l, r))
    
    ans = can_complete_tasks(G, task)
    print(ans)

main()

