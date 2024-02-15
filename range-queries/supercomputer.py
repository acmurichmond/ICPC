class FenwickTree:
    def __init__(self, size):
        self.size = size
        self.tree = [0] * (size + 1)

    def update(self, index, value):
        while index <= self.size:
            self.tree[index] += value
            index += index & -index

    def query(self, index):
        result = 0
        while index > 0:
            result += self.tree[index]
            index -= index & -index
        return result

    def range_query(self, left, right):
        return self.query(right) - self.query(left - 1)

    def flip_bit(self, index):
        # Check current state of the bit (flipped or not)
        current_state = self.range_query(index, index)
        self.update(index, 1 if current_state == 0 else -1)

def main():
    bits, queries = [int(i) for i in input().split(" ")]

    tree = FenwickTree(bits)

    for q in range(queries):
        temp = [i for i in input().split(" ")]

        if(temp[0] == 'F'):
            pos = int(temp[1])
            tree.flip_bit(pos)

        else:
            l, s = int(temp[1]), int(temp[2])
            ans = tree.range_query(l, s)
            print(ans)

main()