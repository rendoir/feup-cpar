#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>
#include <string.h>

#define min(a,b) ((a)<(b)?(a):(b))

using namespace std;

const uint64_t PRINT_THRESHOLD = 5;

void printResultMatrix(double c[], uint64_t size) {
    cout << endl << "Result matrix:" << endl;
    uint64_t n = min(size, (uint64_t)PRINT_THRESHOLD);
    for(uint64_t i = 0; i < n; i++) {
        for(uint64_t j = 0; j < n; j++) {
            if( j != n - 2 && i != n - 2)
                cout << c[i * size + j] << " ";
            else cout << "... ";
        } 
        cout << endl;        
    }
}

void printTime(clock_t time1, clock_t time2) {
    printf("Time: %3.3f seconds\n", (double)(time2 - time1) / CLOCKS_PER_SEC);
}

void columnMultiplication(uint64_t size)
{
	clock_t time1, time2;
	double temp;
    double* a = (double*)(malloc(size*size*sizeof(double)));
    double* b = (double*)(malloc(size*size*sizeof(double)));
    double* c = (double*)(malloc(size*size*sizeof(double)));

    for(uint64_t i = 0; i < size * size; ++i) {
        a[i] = 1;
        b[i] = i / size + 1;
        c[i] = 0;
    }

	time1 = clock();

	for (uint64_t i = 0; i < size; i++) {
		for (uint64_t j = 0; j < size; j++) {
			temp = 0;
			for (uint64_t k = 0; k < size; k++) {
				temp += a[i * size + k] * b[k * size + j];
			}
			c[i * size + j] = temp;
		}
	}

	time2 = clock();
    printTime(time1, time2);

    printResultMatrix(c, size);

    free(a);
    free(b);
    free(c);
}

void lineMultiplication(uint64_t size)
{
	clock_t time1, time2;
    double* a = (double*)(malloc(size*size*sizeof(double)));
    double* b = (double*)(malloc(size*size*sizeof(double)));
    double* c = (double*)(malloc(size*size*sizeof(double)));

    for(uint64_t i = 0; i < size * size; ++i) {
        a[i] = 1;
        b[i] = i / size + 1;
        c[i] = 0;
    }

	time1 = clock();

	for (uint64_t i = 0; i < size; i++)
		for (uint64_t k = 0; k < size; k++) {
            double mat_a_ik = a[i * size + k];
			for (uint64_t j = 0; j < size; j++)
				c[i * size + j] += mat_a_ik * b[k * size + j];
        }

	time2 = clock();
    printTime(time1, time2);

    printResultMatrix(c, size);

    free(a);
    free(b);
    free(c);
}

void blockMultiplication(uint64_t size, uint64_t block_size)
{
    clock_t time1, time2;
    double* a = (double*)(malloc(size*size*sizeof(double)));
    double* b = (double*)(malloc(size*size*sizeof(double)));
    double* c = (double*)(malloc(size*size*sizeof(double)));

    for(uint64_t i = 0; i < size * size; ++i) {
        a[i] = 1;
        b[i] = i / size + 1;
        c[i] = 0;
    }

    time1 = clock();

	for(uint64_t block_hor = 0; block_hor < size; block_hor += block_size)
        for(uint64_t block_ver = 0; block_ver < size; block_ver += block_size)
                for(uint64_t i = 0; i < size; i++)
                        for(uint64_t k = block_hor; k < min(block_hor+block_size, size); k++)
                                for(uint64_t j = block_ver; j<min(block_ver+block_size, size); j++)
                                        c[i*size+j] += a[i*size+k]*b[k*size+j];

    time2 = clock();
    printTime(time1, time2);

    printResultMatrix(c, size);

    free(a);
    free(b);
    free(c);
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
        

    uint64_t size;
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
            uint64_t block_size;
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
