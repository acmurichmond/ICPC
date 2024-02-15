import math
from bitarray import bitarray

def main():
    n, q = map(int, input().split())

    # Setup
    primes = bitarray(n + 1)
    primes.setall(True)
    primes[0], primes[1] = False, False
    m = int(math.sqrt(n))
    count = 0

    # Prime sieve
    for i in range(2, m + 1):
        if primes[i]:
            count += 1
            for j in range(i * 2, n + 1, i):
                primes[j] = False

    # Count extra primes
    for i in range(m + 1, n + 1):
        if primes[i]:
            count += 1

    # Print count of primes
    print(count)

    # Answer all queries
    for _ in range(q):
        query = int(input())
        print(int(primes[query]))

if __name__ == "__main__":
    main()
