import numpy as np

#  Solve the system Ax = b where...
#     A = [1, 2
#          3, 4]
#     b = [1, 2].T
A = np.array([[1, 2], [3, 4]])
b = np.array([1, 2])
x = np.linalg.solve(A, b)
print(x)


# Banded matrix
A = np.array([[1, 4, 0,  0,  0],
              [2, 5, 8,  0,  0],
              [3, 6, 9,  12, 0],
              [0, 7, 10, 13, 15],
              [0, 0, 11, 14, 16]])
b = np.array([1, 2, 3, 4, 5])
x = np.linalg.solve(A, b)
print(x)