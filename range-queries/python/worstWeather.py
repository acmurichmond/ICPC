# limit for array size
N = 100000

# Max size of tree
tree = [0] * (2 * N)

# function to build the tree
def build(arr):
    # insert leaf nodes in tree
    for i in range(n):
        tree[n + i] = arr[i]

    # build the tree by calculating parents
    for i in range(n - 1, 0, -1):
        tree[i] = max(tree[i * 2], tree[i * 2 + 1])


# function to get maximum number on interval [l, r)
def query(l, r):
    res = float('-inf')

    l += n
    r += n

    while l < r:
        if (l % 2) == 1:
            res = max(res, tree[l])
            l += 1

        if (r % 2) == 1:
            r -= 1
            res = max(res, tree[r])

        l //= 2
        r //= 2

    return res

# find lower limit
def binarySearch(ls, target):
    l, r = 0, len(ls) - 1

    while(l < r):
        mid = l + (r - l) // 2
        if(ls[mid] < target):
            l = mid + 1
        elif(ls[mid] > target):
            r = mid
    
    return l

# find upper limit
def binarySearchUpper(ls, target):
    l, r = 0, len(ls) - 1

    while(l < r):
        mid = l + (r - l + 1) // 2
        if(ls[mid] > target):
            r = mid - 1
        elif(ls[mid] < target):
            l = mid
    
    return r


# Driver Code
if __name__ == "__main__":
    while True:
        m = int(input())
        index = 0

        hashmap = {}

        yearList = []
        rainList = []

        for i in range(0, m):
            yearRain = [int(i) for i in input().split(" ")]
            yearList.append(yearRain[0])
            rainList.append(yearRain[1])
            hashmap[yearRain[0]] = index
            index += 1

        # query number
        nm = int(input())

        # Exit when m and n are 0
        if (m == 0 and nm == 0):
            break

        # n is global
        n = len(rainList)

        # build tree
        build(rainList)

        for i in range(0, nm):
            yearSE = [int(i) for i in input().split(" ")]

            # Handle situation such that both year is unknow
            if(yearSE[0] not in hashmap and yearSE[1] not in hashmap):
                print('maybe')
                continue

            # Handle situation such that X_year is unknown
            if(yearSE[1] not in hashmap):

                if(yearSE[1] < yearList[-1]):
                    closeYear = binarySearchUpper(yearList, yearSE[1])
                    MaxRain = query(hashmap[yearSE[0]] + 1, closeYear + 1)
                    if(MaxRain >= rainList[hashmap[yearSE[0]]]):
                        print('false')
                    else:
                        print('maybe')
                    continue
                else:
                    MaxRain = query(hashmap[yearSE[0]] + 1, len(yearList))
                    if(MaxRain >= rainList[hashmap[yearSE[0]]]):
                        print('false')
                    else:
                        print('maybe')
                    continue

            # Handle situation such that Y_year is unknown
            if(yearSE[0] not in hashmap):
                if(yearSE[0] < yearList[0]):
                    MaxRain = query(0, hashmap[yearSE[1]])
                    if(MaxRain >= rainList[hashmap[yearSE[1]]]):
                        print('false')
                    else:
                        print('maybe')
                    continue
                elif(yearSE[0] > yearList[0]):
                    closeYear = binarySearch(yearList, yearSE[0])
                    MaxRain = query(closeYear, hashmap[yearSE[1]])
                    if(MaxRain >= rainList[hashmap[yearSE[1]]]):
                        print('false')
                    else:
                        print('maybe')
                    continue

            maxRainBetween = query(hashmap[yearSE[0]] + 1, hashmap[yearSE[1]])
            yearDiff = yearSE[1] - yearSE[0]
            indexDiff = hashmap[yearSE[1]] - hashmap[yearSE[0]]
            X_year, Y_year = rainList[hashmap[yearSE[1]]], rainList[hashmap[yearSE[0]]]


            if(yearDiff == indexDiff and X_year > maxRainBetween and X_year <= Y_year):
                print('true')
            elif(yearDiff != indexDiff and X_year > maxRainBetween and X_year <= Y_year):
                print('maybe')
            else:
                print('false')

        blank = input()