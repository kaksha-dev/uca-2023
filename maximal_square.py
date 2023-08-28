'''
https://leetcode.com/problems/maximal-square/description
'''

def maximal_square(matrix):
    '''
    Given an m x n binary matrix filled with 0's and 1's, find the largest square containing
    only 1's and return its area.
    '''
    rows = len(matrix)
    cols = len(matrix[0])

    # 1*1 matrix
    if rows == 1 and cols == 1:
        return int(matrix[0][0])

    # Return 1 if there is a 1 in the martix of 1 row, 0 otherwise.
    if rows == 1:
        return max(map(int, matrix[0]))

    # Return 1 if there is a 1 in the martix of 1 column, 0 otherwise.
    if cols == 1:
        for i in range(rows):
            if matrix[i][0] == '1':
                return 1
        return 0

    output = [[0 for _ in range(cols)] for _ in range(rows)]

    max_square = 0
    # Initialize first column.
    for i in range(rows):
        if matrix[i][0] == '1':
            max_square = 1
            output[i][0] = 1

    # Initialize first row.
    for j in range(cols):
        if matrix[0][j] == '1':
            max_square = 1
            output[0][j] = 1

    # Recurrence relation.
    for i in range(1, rows):
        for j in range(1, cols):
            if matrix[i][j] == '0':
                continue
            output[i][j] = 1 + min(output[i][j-1], output[i-1][j-1], output[i-1][j])
            if output[i][j] > max_square:
                max_square = output[i][j]

    return max_square*max_square

# Test Cases.
assert maximal_square(
    [["1","0","1","0","0"],
     ["1","0","1","1","1"],
     ["1","1","1","1","1"],
     ["1","0","0","1","0"]]) == 4
assert maximal_square([["0","1"],["1","0"]]) == 1
assert maximal_square([["0"]]) == 0
