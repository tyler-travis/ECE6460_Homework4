// File: main.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include "NPE.hpp"

int main(int argc, char** argv)
{
    NPE npe("input_file.txt");
    std::cout << "NPE: " << npe.get_NPE() << std::endl;
    return 0;
}
