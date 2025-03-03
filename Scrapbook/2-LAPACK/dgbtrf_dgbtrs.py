import numpy as np
from scipy.linalg import lu_factor, lu_solve

# Define a banded matrix A and a right-hand side vector b
A = np.array([[1, 4, 0 , 0 , 0 ],
              [2, 5, 8 , 0 , 0 ],
              [3, 6, 9 , 12, 0 ],
              [0, 7, 10, 13, 15],
              [0, 0, 11, 14, 16]], dtype=float)

b = np.array([1, 2, 3, 4, 5], dtype=float)

# Compute LU decomposition and solve
LU, piv = lu_factor(A)
# print(LU)
# print(piv)
x = lu_solve((LU, piv), b)

# Verify the solution
print("Solution x:", x)
# print("Verification (Ax):")
# print(f"A @ x: {A @ x}")
# print(f"b:     {b}")

