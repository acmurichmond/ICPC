#Written by Joseph.
#Reviewed by Andrew, 2.1.24. matrixAdd, matrixMult, matrixPower look correct. gauss_jordan_inverse, eigenDecomp unclear if work. 
#zip(*matrix) gives transpose
from fractions import Fraction
import math

def matrixAdd(matrix_A, matrix_B):
    return [[matrix_A[i][j] + matrix_B[i][j]  for j in range (len(matrix_A[0]))] for i in range(len(matrix_A))]

def matrixMult(matrix_A, matrix_B):
    #O(n^3) 
    return [[sum(A * B for A, B in zip(row_A, col_B)) for col_B in zip(*matrix_B)] for row_A in matrix_A]

def matrixPower(matrix_A, n):
    #O(n^3 log k)
    if n == 0:
        #basecase identity matrix
        length_A = len(matrix_A)
        return [[1 if i == j else 0 for j in range(length_A)] for i in range(length_A)]

    elif n % 2 == 0:
        #even
        temp = matrixPower(matrix_A, n // 2)
        return matrixMult(temp, temp)
    else:
        #odd
        return matrixMult(matrix_A, matrixPower(matrix_A, n - 1))


#all below is for eigenvalue decomp. only
def gauss_jordan_inverse(matrix):
    n = len(matrix)
    temp = [row + [1 if i == j else 0 for j in range(n)] for i, row in enumerate(matrix)]

    for col in range(n):
        pivot = max(range(col, n), key=lambda i: abs(temp[i][col]))
        temp[col], temp[pivot] = temp[pivot], temp[col]
        val = temp[col][col]
        temp[col] = [Fraction(entry,val) for entry in temp[col]]

        for i in range(n):
            if i != col:
                factor = temp[i][col]
                temp[i] = [entry - factor * temp[col][j] for j, entry in enumerate(temp[i])]

    return [row[n:] for row in temp]


def eigenDecomp(matrix, eigenvalues, eigenvectors, n):
    # Wrote the eigenvalue decomp with the assumption evalue+vectors are given. If not, then (without numpy) the eigenvalues/vectors need to be found via power iteration, qr algorithm, etc.
    # Wasn't sure if that's what we wanted 

    matrixlen = len(matrix)
    powered_diagonal = [[float(pow(eigenvalue, n)) if i == j else 0 for j in range(matrixlen)] for i, eigenvalue in enumerate(eigenvalues)]
    return matrixMult(matrixMult(eigenvectors, powered_diagonal), gauss_jordan_inverse(eigenvectors))


def main():
    matrix_A = [[1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]]
    matrix_B = [[-26, -33, -25],
                [31, 42, 23],
                [-11, -15, -4]]


    # An, Bn = list(map(int, input().split()))
    # matrix_A = [list(map(int, input().split())) for _ in range(An)]
    # matrix_B = [list(map(int, input().split())) for _ in range(Bn)]
 
    print(matrixAdd(matrix_A, matrix_B))
    print(matrixMult(matrix_A, matrix_B))
    print(matrixPower(matrix_A, 2))
    print(matrixPower(matrix_B, 5))

    eigenvalues = [-6, 3, 15] #for matrix_B
    eigenvectors = [[7, -2, 1],[-5, 1, -2], [1, 1, 1]] #for matrix_B
    power = 5

    print(eigenDecomp(matrix_B, eigenvalues, eigenvectors, power))

if __name__ == "__main__":
	main()