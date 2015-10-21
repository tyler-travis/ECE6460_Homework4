

#ifndef NPE_HPP
#define NPE_HPP

#include <string>
#include "slicing_tree"

class NPE
{
private:
    // Contains the Normalized Polish Expression (NPE)
    std::string expression;

    // The slicing_tree corresponding to the NPE
    slicing_tree tree;

    // moves 1, 2, and 3
    const std::string move1();
    const std::string move2();
    const std::string move3();

public:
    // Default constructor
    NPE();

    // Takes a filename to open the file and populate the module list
    NPE(std::string);
    
    // Takes an int, either 1, 2, or 3 corresponding to m1, m2, or m3.
    void move(int); 

    // Create the module list from a file
    void set_module_list(std::string);

    // Getter and setter for the NPE
    // Might not need to set the NPE but we'll see.
    std::string get_NPE(void);
    void set_NPE(std::string);


};

#endif
