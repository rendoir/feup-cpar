from time import process_time as pt

def initMatrices(size):
    return ([1 for i in range(size*size)], [int(i/size)+1 for i in range(size*size)], [0 for i in range(size*size)])

def columnMultiplication(size):
    mat_a, mat_b, mat_c = initMatrices(size)

    start = pt()

    for i in range(size):
        for j in range(size):
            temp = 0
            for k in range(size):
                temp += mat_a[i][k] * mat_b[k][j]
            mat_c[i][j] = temp

    stop = pt()

    print([mat_c[0][i] for i in range(min(10, size))])
    print("Time: ", end="")
    print(stop-start)

def lineMultiplication(size):
    mat_a, mat_b, mat_c = initMatrices(size)

    start = pt()

    for i in range(size):
        for k in range(size):
            for j in range(size):
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j]

    stop = pt()

    print([mat_c[0][i] for i in range(min(10, size))])
    print("Time: ", end="")
    print(stop-start)

def blockMultiply(size, blockSize):
    mat_a, mat_b, mat_c = initMatrices(size)

    start = pt()

    for bi in range(0, size, blockSize):
        for bk in range(0, size, blockSize):
            for bj in range(0, size, blockSize):
                for i in [ind for ind in range(blockSize) if bi + ind < size]:
                    for k in [ind for ind in range(blockSize) if bk + ind < size]:
                        for j in [ind for ind in range(blockSize) if bj + ind < size]:
                            mat_c[(bi + i) * size + (bj + j)] += mat_a[(bi + i) * size + (bk + k)] * mat_b[(bk + k) * size + (bj + j)]

    stop = pt()

    print([mat_c[i] for i in range(min(10, size))])
    print("Time: ", end="")
    print(stop-start)


if __name__ == '__main__':
    while True:
        print('1. Multiplication')
        print('2. Line Multiplication')
        print('3. Partitioned Multiplication')
        
        option = int(input('Selection: '))
        if option == 0:
            break

        size = int(input('Matrix size: '))

        if option == 1:
            onMult(size)
        elif option == 2:
            onMultLine(size)
        elif option == 4:
            onMultLineNumpy(size)
        elif option == 3:
            blockSize = int(input('Block size: '))
            blockMultiply(size, blockSize)

