// File: main.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include <cstdlib>
#include "NPE.hpp"

int main(int argc, char** argv)
{
    NPE npe("input_file.txt");
    std::cout << "NPE: " << npe.get_NPE() << std::endl;
    std::cout << "M1:  " << npe.M1() << std::endl;
    std::cout << "M2:  " << npe.M2() << std::endl;
    std::cout << "M3:  " << npe.M3() << std::endl;
    return 0;
}
