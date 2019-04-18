#include "SequentialSieve.h"
#include "OpenMPSieve.h"

#include <iostream>

using namespace std;


void run()
{
    unsigned int option;

    while(true) {
        cout << endl;
        cout << "1. Sequential" << endl;
        cout << "2. OpenMP" << endl;
        cout << "0. Exit" << endl;
        cout << "Option: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
            case 0:
                return;
        
            case 1:
                SequentialSieveOfEratosthenes::test();
                break;

            case 2:
                OpenMPSieveOfEratosthenes::test();
                break;

            default:
                break;
        }
    }
}

int main (int argc, char *argv[])
{
    run();
}
