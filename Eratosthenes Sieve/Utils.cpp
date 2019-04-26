#include "Utils.h"
#include <iostream>

using namespace std;


bool Parameters::automatic;
std::string Parameters::algorithm;
int Parameters::threads;
int Parameters::processes;
int Parameters::lower_exponent;
int Parameters::upper_exponent;
int Parameters::current_exponent;

int parseParameters(int argc, char** argv)
{
    if(argc <= 1) {
        Parameters::automatic = false;
        return 0;
    }

    if(argc >= 4) {
        Parameters::automatic = true;
        Parameters::algorithm = argv[1];
        Parameters::lower_exponent = stoi(argv[2]);
        Parameters::upper_exponent = stoi(argv[3]);
        Parameters::current_exponent = Parameters::lower_exponent;
    } else return -1;

    if(Parameters::algorithm == "omp" && argc == 5)
        Parameters::threads = stoi(argv[4]);
    else if(Parameters::algorithm == "mpi" && argc == 5)
        Parameters::processes = stoi(argv[4]);
    else if(Parameters::algorithm == "hybrid" && argc == 6) {
        Parameters::threads = stoi(argv[4]);
        Parameters::processes = stoi(argv[5]);
    } else if(Parameters::algorithm != "sequential")
        return -1;

    return 0;
}

void printUsage() {
    cout << "TODO" << endl;
}
