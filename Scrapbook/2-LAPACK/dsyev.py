import numpy as np


A = np.array([[4, -2, 2],
              [-2, 5, -3],
              [2, -3, 6]])

eigval, eigvect = np.linalg.eig(A)

for i in range(3):
    print(f"Eigenvalue {i}: {eigval[i]}")
    print(f"Eigvector: {eigvect[:, i]}\n")