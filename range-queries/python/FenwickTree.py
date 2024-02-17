'''
Fenwick Tree is a data structure that provides efficient methods for
performing operations on cumulative frequency tables. For example prefix sum, update cost O(logn)
'''

class FenwickTree:
    def __init__(self, size):
        # Initialize fenwick tree with a specific size
        self.size = size
        self.tree = [0] * (size + 1)

    def update(self, index, value):
        # Update the tree with a value at a specific index
        while index <= self.size:
            self.tree[index] += value
            index += index & -index

    def query(self, index):
        # Query the sum from the beginning of the array to a specific index
        result = 0
        while index > 0:
            result += self.tree[index]
            index -= index & -index
        return result

    def range_query(self, left, right):
        # Query the sum of a specific range [left, right]
        return self.query(right) - self.query(left - 1)
    