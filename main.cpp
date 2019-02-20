//#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>
#include <string.h>

using namespace std;

#define PRINT_THRESHOLD 5
#define SYSTEMTIME clock_t

void initMatrices(double **&a, double **&b, double **&c, unsigned long int size) {
    a = (double **)malloc((size) * sizeof(double*));
    b = (double **)malloc((size) * sizeof(double*));
    c = (double **)malloc((size) * sizeof(double*));

    for(int i = 0; i < size; i++) {
        a[i] = (double *)malloc((size) * sizeof(double));
        b[i] = (double *)malloc((size) * sizeof(double));
        c[i] = (double *)malloc((size) * sizeof(double));

        for(int j = 0; j < size; j++) {
            a[i][j] = 1;
            b[i][j] = i + 1;
            c[i][j] = 0;
        }
    }
}

void destroyMatrices(double **&a, double **&b, double **&c, unsigned long int size) {
    for(int i = 0; i < size; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }

    free(a);
    free(b);
    free(c);
}

void printResultMatrix(double **&c, unsigned long int size) {
    cout << endl << "Result matrix:" << endl;
    unsigned int n = min(size, (unsigned long int)PRINT_THRESHOLD);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if( j != n - 2 && i != n - 2)
                cout << c[i][j] << " ";
            else cout << "... ";
        } 
        cout << endl;        
    }
}

void columnMultiplication(unsigned long int size)
{
	SYSTEMTIME Time1, Time2;

	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;

	pha = (double *)malloc((size * size) * sizeof(double));
	phb = (double *)malloc((size * size) * sizeof(double));
	phc = (double *)malloc((size * size) * sizeof(double));

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			pha[i * size + j] = (double)1.0;

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			phb[i * size + j] = (double)(i + 1);

	Time1 = clock();

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			temp = 0;
			for (k = 0; k < size; k++) {
				temp += pha[i * size + k] * phb[k * size + j];
			}
			phc[i * size + j] = temp;
		}
	}

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	cout << "Result matrix: " << endl;
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < min((unsigned long int)10, size); j++)
			cout << phc[j] << " ";
	}

	free(pha);
	free(phb);
	free(phc);
}

void lineMultiplication(unsigned long int size)
{
	SYSTEMTIME Time1, Time2;

	char st[100];
	int i, j, k;

	double *pha, *phb, *phc;
	int block_size = 5;

	pha = (double *)malloc((size * size) * sizeof(double));
	phb = (double *)malloc((size * size) * sizeof(double));
	phc = (double *)malloc((size * size) * sizeof(double));

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			pha[i * size + j] = (double)1.0;

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			phb[i * size + j] = (double)(i + 1);

	memset(phc, 0, sizeof phc);

	Time1 = clock();

	for (i = 0; i < size; i++)
		for (k = 0; k < size; k++)
			for (j = 0; j < size; j++)
				phc[i * size + j] += pha[i * size + k] * phb[k * size + j];

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	cout << "Result matrix: " << endl;
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < min((unsigned long int)10, size); j++)
			cout << phc[j] << " ";
	}

	free(pha);
	free(phb);
	free(phc);
}

void blockMultiplication(unsigned long int size, unsigned long int block_size)
{
    double **a, **b, **c;
    initMatrices(a, b, c, size);

	for (int bi = 0; bi < size; bi += block_size)
		for (int bk = 0; bk < size; bk += block_size)
			for (int bj = 0; bj < size; bj += block_size)
				for (int i = 0; i < block_size && bi + i < size; i++)
					for (int k = 0; k < block_size && bk + k < size; k++)
						for (int j = 0; j < block_size && bj + j < size; j++)
							c[bi + i][bj + j] += a[bi + i][bk + k] * b[bk + k][bj + j];

    printResultMatrix(c, size);
    destroyMatrices(a, b, c, size);
}

int main(int argc, char *argv[])
{
	int event_set = PAPI_NULL;
	long long cache_misses[2];
	int ret;

	ret = PAPI_library_init(PAPI_VER_CURRENT);
	if (ret != PAPI_VER_CURRENT)
		cerr << "PAPI Error: Init" << endl;

	ret = PAPI_create_eventset(&event_set);
	if (ret != PAPI_OK)
		cerr << "PAPI Error: Create eventset" << endl;

	ret = PAPI_add_event(event_set, PAPI_L1_DCM);
	if (ret != PAPI_OK)
		cerr << "PAPI Error: Add event PAPI_L1_DCM" << endl;

	ret = PAPI_add_event(event_set, PAPI_L2_DCM);
	if (ret != PAPI_OK)
		cerr << "PAPI Error: Add event PAPI_L2_DCM" << endl;

    unsigned long int size;
	int option = 0;
	do
	{
        cout << "1. Column Multiplication" << endl;
        cout << "2. Line Multiplication" << endl;
        cout << "3. Block Multiplication" << endl;
        cout  << "0. Exit" << endl;
        cout << "Option: ";
        cin >> option;

        if(!option)
            break;

        cout << endl << "Matrix size: ";
        cin >> size;

        ret = PAPI_start(event_set);
        if (ret != PAPI_OK)
    		cerr << "PAPI Error: Start" << endl;

        switch (option) {
        case 1:
            columnMultiplication(size);
            break;
        case 2:
            lineMultiplication(size);
            break;
        case 3:
            unsigned long long int block_size;
            cout << "Block size: ";
            cin >> block_size;
            blockMultiplication(size, block_size);
            break;
        default:
            break;
        }

        cout << endl;
        
		ret = PAPI_stop(event_set, cache_misses);
		if (ret != PAPI_OK)
		    cerr << "PAPI Error: Stop" << endl;
		printf("L1 DCM: %lld \n", cache_misses[0]);
		printf("L2 DCM: %lld \n", cache_misses[1]);

		ret = PAPI_reset(event_set);
		if (ret != PAPI_OK)
    		cerr << "PAPI Error: Reset" << endl;

        cout << endl;

	} while (option != 0);

	ret = PAPI_remove_event(event_set, PAPI_L1_DCM);
	if (ret != PAPI_OK)
		cerr << "PAPI Error: Remove event PAPI_L1_DCM" << endl;

	ret = PAPI_remove_event(event_set, PAPI_L2_DCM);
	if (ret != PAPI_OK)
		cerr << "PAPI Error: Remove event PAPI_L2_DCM" << endl;

	ret = PAPI_destroy_eventset(&event_set);
	if (ret != PAPI_OK)
		cerr << "PAPI Error: Destroy eventset" << endl;
}