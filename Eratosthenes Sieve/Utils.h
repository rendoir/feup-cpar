#ifndef UTILS_H
#define UTILS_H

#include <string>

struct Parameters
{
    static bool automatic;
    static std::string algorithm;
    static int threads;
    static int processes;
    static int lower_exponent;
    static int upper_exponent;
    static int current_exponent;
    static std::string output_file;
};

int parseParameters(int argc, char** argv);
void printUsage();

#endif
