// File: NPE.hpp
// Author: Tyler Travis
// A#: A01519795
// Homework 4

#ifndef NPE_HPP
#define NPE_HPP

#include <string>
#include <random>
#include "slicing_tree.hpp"

class NPE
{
private:
    // Contains the Normalized Polish Expression (NPE)
    std::string expression;

    // The slicing_tree corresponding to the NPE
    slicing_tree tree;

    // Random number generator
    std::random_device rd;

    // Verifies that an expression will be vaild after a move
    bool verify(unsigned int, unsigned int);

public:
    // Default constructor
    NPE();

    // Takes a filename to open the file and populate the module list
    NPE(std::string);
   
    // Takes a filename and an expression to open the file and populate the module list
    NPE(std::string, std::string);

    // Getter for the NPE
    const std::string get_NPE(void);

    // Setter for the NPE
    void set_NPE(std::string);

    // M1: Swap two adjacent operands
    std::string M1();

    // M2: Complement some chain of nonzero length
    std::string M2();

    // M3: Swap two adjacent operand and operator
    // (Need to check if still normailized after swap)
    std::string M3();

    // Print the corrisponding tree
    void print_tree();

    // Get the cost of the current NPE
    double cost();

    // Get the number of operands for the expression
    int get_number_of_operands();

};

#endif
