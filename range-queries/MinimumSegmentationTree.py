# Minimum segmentation trees

# limit for array size
N = 100000

# Max size of tree
tree = [float('inf')] * (2 * N)

# function to build the tree
def build(arr):
    # insert leaf nodes in tree
    for i in range(n):
        tree[n + i] = arr[i]

    # build the tree by calculating parents
    for i in range(n - 1, 0, -1):
        tree[i] = min(tree[i * 2], tree[i * 2 + 1])


# function to update a value in the array and rebuild the segment
def update(index, value):
    # set value at position p
    tree[index + n] = value
    index += n

    # move upward and update parents
    i = index

    while i > 1:
        i //= 2
        tree[i] = min(tree[i * 2], tree[i * 2 + 1])

# function to get minimum number on interval [l, r)
def query(l, r):
    res = float('inf')

    l += n
    r += n

    while l < r:
        if (l % 2) == 1:
            res = min(res, tree[l])
            l += 1

        if (r % 2) == 1:
            r -= 1
            res = min(res, tree[r])

        l //= 2
        r //= 2

    return res

# Example Usage
arr = [1, 3, 5, 7, 9, 11]
n = len(arr)
build(arr)
