#include "SequentialSieve.h"
#include "OpenMPSieve.h"
#include "OpenMPISieve.h"
#include "HybridSieve.h"
#include "Utils.h"

#include <iostream>

using namespace std;


int runManual()
{
    unsigned int option;

    while(true) {
        cout << endl;
        cout << "1. Sequential" << endl;
        cout << "2. OpenMP" << endl;
        cout << "3. OpenMPI" << endl;
        cout << "4. Hybrid" << endl;
        cout << "0. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
            case 0:
                return 0;
        
            case 1:
                SequentialSieveOfEratosthenes::test();
                break;

            case 2:
                OpenMPSieveOfEratosthenes::test();
                break;

            case 3:
                OpenMPISieveOfEratosthenes::test();
                break;

            case 4:
                HybridSieveOfEratosthenes::test();
                break;

            default:
                break;
        }
    }

    return 0;
}

int runAuto() 
{ 
    while(Parameters::current_exponent <= Parameters::upper_exponent) {
        if(Parameters::algorithm == "sequential")
            SequentialSieveOfEratosthenes::test();
        else if(Parameters::algorithm == "omp")
            OpenMPSieveOfEratosthenes::test();
        else if(Parameters::algorithm == "mpi")
            OpenMPISieveOfEratosthenes::test();
        else if(Parameters::algorithm == "hybrid")
            HybridSieveOfEratosthenes::test();
        else return -1;

        Parameters::current_exponent++;
    }

    return 0;
}

int run(int argc, char *argv[])
{
    if(parseParameters(argc, argv) == -1) {
        printUsage();
        return -1;
    }
        
    if(Parameters::automatic)
        return runAuto();
    else return runManual();
}

int main (int argc, char *argv[])
{
    return run(argc, argv);
}
