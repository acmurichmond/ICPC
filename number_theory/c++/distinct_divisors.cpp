// Finds All Distinct Divisors
// in sorted order
// #include <bits/stdc++.h>
using namespace std;

#include <vector>
#include <cmath>

std::vector<int> get_divisors(int n) {
    std::vector<int> divisors;

    for (int i = 1; i <= std::sqrt(n); i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }

    return divisors;
}






// TBDeleted
/* Driver program to test above function */
#include <cstdio>
#include <vector>

int main()
{
    printf("The divisors of 100 are: \n");
    std::vector<int> vect = get_divisors(10);
    for (int i = 0; i < vect.size(); i++) {
        printf("%d ", vect[i]);
    }
    return 0;
}

