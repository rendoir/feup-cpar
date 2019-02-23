from time import process_time as pt

def init_matrices(size):
    return ([1 for i in range(size*size)], [int(i/size)+1 for i in range(size*size)], [0 for i in range(size*size)])

def column_multiplication(size):
    mat_a, mat_b, mat_c = init_matrices(size)

    start = pt()

    for i in range(size):
        for j in range(size):
            temp = 0
            for k in range(size):
                temp += mat_a[i * size + k] * mat_b[k * size + j]
            mat_c[i * size + j] = temp

    stop = pt()

    print([mat_c[i] for i in range(min(10, size))])
    print("Time: ", end="")
    print(stop-start)

def line_multiplication(size):
    mat_a, mat_b, mat_c = init_matrices(size)

    start = pt()

    for i in range(size):
        for k in range(size):
            for j in range(size):
                mat_c[i * size + j] += mat_a[i * size + k] * mat_b[k * size + j]

    stop = pt()

    print([mat_c[i] for i in range(min(10, size))])
    print("Time: ", end="")
    print(stop-start)

def block_multiplication(size, block_size):
    mat_a, mat_b, mat_c = init_matrices(size)

    start = pt()

    for bi in range(0, size, block_size):
        for bk in range(0, size, block_size):
            for bj in range(0, size, block_size):
                for i in [ind for ind in range(block_size) if bi + ind < size]:
                    for k in [ind for ind in range(block_size) if bk + ind < size]:
                        for j in [ind for ind in range(block_size) if bj + ind < size]:
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
            column_multiplication(size)
        elif option == 2:
            line_multiplication(size)
        elif option == 3:
            block_size = int(input('Block size: '))
            block_multiplication(size, block_size)

