// Matrix Exponentiation
// C++
#include <iostream>
#include <vector>

using namespace std;

typedef vector< vector<int> > matrix;

matrix matrixMultiply(const matrix &a, const matrix &b) {
    int n = a.size();
    matrix result(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

matrix matrixPower(matrix a, int n) {
    if (n == 0) {
        matrix identity(a.size(), vector<int>(a.size(), 0));
        for (int i = 0; i < a.size(); i++) {
            identity[i][i] = 1;
        }
        return identity;
    } else if (n == 1) {
        return a;
    } else if (n % 2 == 0) {
        return matrixPower(matrixMultiply(a, a), n / 2);
    } else {
        return matrixMultiply(a, matrixPower(matrixMultiply(a, a), (n - 1) / 2));
    }
}

void printMatrix(const matrix &m) {
    for (const auto &row : m) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    matrix A = {{2, 1}, {1, 2}};
    int n = 3;

    cout << "Matrix A:" << endl;
    printMatrix(A);

    matrix result = matrixPower(A, n);
    cout << "A raised to power " << n << ":" << endl;
    printMatrix(result);

    return 0;
}

