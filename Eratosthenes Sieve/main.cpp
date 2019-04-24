#include "SequentialSieve.h"
#include "OpenMPSieve.h"
#include "OpenMPISieve.h"
#include "HybridSieve.h"

#include <iostream>

using namespace std;


void run(int argc, char** argv)
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
                return;
        
            case 1:
                SequentialSieveOfEratosthenes::test(argc, argv);
                break;

            case 2:
                OpenMPSieveOfEratosthenes::test(argc, argv);
                break;

            case 3:
                OpenMPISieveOfEratosthenes::test(argc, argv);
                break;

            case 4:
                HybridSieveOfEratosthenes::test(argc, argv);
                break;

            default:
                break;
        }
    }
}

int main (int argc, char *argv[])
{
    run(argc, argv);
}
