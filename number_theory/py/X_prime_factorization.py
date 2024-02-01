# Prime Factorization
# Python 3
import math 
def primeFactors(n): 
    primes = []
    while n % 2 == 0: 
        primes.append(int(2)), 
        n = n / 2
    for i in range(3,int(math.sqrt(n))+1,2): 
        while n % i== 0: 
            primes.append(int(i))
            n = n / i          
    if n > 2: 
        primes.append(int(n))
    return primes


#The rest is open kattis test case - under review
from sys import stdin
for line in stdin:
    string = ""
    nbr = int(line)
    l = []
    if nbr < 0:
        l.append(-1)
        nbr = nbr * -1
    l = l + primeFactors(nbr)
    temp_tally = 1
    past_factor = l[0]
    for idx in range(1, len(l)):
        factor = l[idx]
        if factor == past_factor:
            temp_tally +=1
        else:
            if temp_tally > 1:
                print(str(past_factor) + "^" + str(temp_tally), end = " ")
            else:
                print(past_factor, end = " ")
            temp_tally = 1
            past_factor = factor
    if temp_tally > 1:
        print(str(past_factor) + "^" + str(temp_tally))
    else:
        print(past_factor)
