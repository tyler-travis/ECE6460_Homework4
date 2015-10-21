

#ifndef NPE_HPP
#define NPE_HPP

#include <string>
#include "slicing_tree.hpp"

class NPE
{
private:
    // Contains the Normalized Polish Expression (NPE)
    std::string expression;

    // The slicing_tree corresponding to the NPE
    slicing_tree tree;

public:
    // Default constructor
    NPE();

    // Takes a filename to open the file and populate the module list
    NPE(std::string);

    // Getter for the NPE
    const std::string get_NPE(void);


};

#endif
