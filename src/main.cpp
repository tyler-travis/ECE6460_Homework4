// File: main.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include "slicing_tree.hpp"

int main(int argc, char** argv)
{
    std::string NPEa = "12H3H4H5H6H7H8H9HaHbHcHdHeHfHgHiHjHkHlH";
    std::string NPEb = "12V3V4V5V6V7V8V9VaVbVcVdVeVfVgViVjVkVlV";
    std::string NPEc = "213546H7VHVa8V9HcVHgHibdHkVHfeHVlHVjHVH";
    slicing_tree test, test1, test2;
    test.import_module_list("input_file.txt");
    test1.import_module_list("input_file.txt");
    test2.import_module_list("input_file.txt");
    double cost = test.cost(NPEa);
    double cost1 = test1.cost(NPEb);
    double cost2 = test2.cost(NPEc);
    std::cout << "NPE: " << NPEa << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "NPE: " << NPEb << std::endl;
    std::cout << "cost: " << cost1 << std::endl;
    std::cout << "NPE: " << NPEc << std::endl;
    std::cout << "cost: " << cost2 << std::endl;
    return 0;
}
