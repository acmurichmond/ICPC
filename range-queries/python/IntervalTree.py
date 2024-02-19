'''
An Interval Tree is a binary search tree designed for storing intervals 
and efficiently querying them. Each node in the tree represents an interval 
and stores the maximum end-point of intervals in its subtree. The tree is 
organized based on the starting points of these intervals. Its primary 
function is to quickly find all intervals that overlap with any given interval 
or point. This makes it highly useful in scenarios where such overlap checks 
are frequent and the dataset of intervals is dynamic, allowing for efficient 
insertions and deletions. Its typical applications include computational geometry, 
scheduling, and various range querying
'''


class Interval:
    def __init__(self, start, end):
        # Constructor for the Interval class
        # start - beginning of the interval
        # end - end of the interval
        self.start = start
        self.end = end

class Node:
    def __init__(self, interval):
        # Constructor for the Node class
        # interval - the interval object associated with the node
        # max - maximum end point within the subtree rooted at this node
        self.interval = interval
        self.max = interval.end
        self.left = None
        self.right = None

class IntervalTree:
    def __init__(self):
        # Constructor for the IntervalTree class
        # Initializes the root of the tree to None
        self.root = None

    def insert(self, root, interval):
        # Inserts an interval into the tree and returns the new root
        # root - the current root of the subtree
        # interval - the interval to insert
        if root is None:
            return Node(interval)

        # Insert based on the start of the interval
        if interval.start < root.interval.start:
            root.left = self.insert(root.left, interval)
        else:
            root.right = self.insert(root.right, interval)

        # Update the max value of the root
        root.max = max(root.max, interval.end)
        return root

    def overlap_search(self, root, interval):
        # Searches for any interval in the tree that overlaps with the given interval
        # root - the current root of the subtree
        # interval - the interval to check for overlap
        if root is None:
            return False

        # Check if intervals overlap
        if self.do_overlap(root.interval, interval):
            return True

        # Traverse left subtree if it may contain an overlapping interval
        if root.left is not None and root.left.max >= interval.start:
            if self.overlap_search(root.left, interval):
                return True

        # Otherwise, traverse the right subtree
        return self.overlap_search(root.right, interval)

    @staticmethod
    def do_overlap(interval1, interval2):
        # Checks if two intervals overlap
        # interval1, interval2 - intervals to compare
        return (interval1.start < interval2.end) and (interval2.start < interval1.end)

    def in_order_traversal(self, root):
        # Performs an inorder traversal of the tree and prints each interval
        # root - the current root of the subtree
        if root is not None:
            self.in_order_traversal(root.left)
            print(f"{root.interval} with max = {root.max}")
            self.in_order_traversal(root.right)




# Example Usage
it = IntervalTree()
intervals = [Interval(15, 20), Interval(10, 30), Interval(17, 19),
             Interval(5, 20), Interval(12, 15), Interval(30, 40)]

for interval in intervals:
    it.root = it.insert(it.root, interval)

print("Inorder traversal of constructed Interval Tree is")
it.in_order_traversal(it.root)

search_interval = Interval(6, 7)
print("Searching for interval")
print("Overlap found:", it.overlap_search(it.root, search_interval))