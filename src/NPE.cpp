// File: NPE.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 4

#include "NPE.hpp"

NPE::NPE()
{
}

NPE::NPE(std::string fileName)
{
    // Import the module list for the tree
    tree.import_module_list(fileName);

    // Get the module names from the tree
    std::string temp = tree.get_module_names();

    // If the expression isn't empty, clear it
    if(!expression.empty())
    {
        expression.clear();
    }

    // Push on the first element
    expression.push_back(temp[0]);

    // Alternate operand and operator to get a structure like:
    // 12V34V5V6V...
    for(unsigned int i = 1; i < temp.size(); ++i)
    {
        expression.push_back(temp[i]);
        expression.push_back('V');
    }
    
    // Create a tree from that expression
    tree.create_tree(expression);
}

// Constructor for a module list and expression
NPE::NPE(std::string fileName, std::string _expression)
{
    // Set the expression equal to the new expression
    expression = _expression;

    // Import the module list
    tree.import_module_list(fileName);

    // Create a tree from the given expression
    tree.create_tree(expression);
}


const std::string NPE::get_NPE(void)
{
    return expression;
}

void NPE::set_NPE(std::string _expression)
{
    // Delete the tree in order to create a new one
    tree.delete_tree();

    // Update the expression
    expression = _expression;

    // Create a tree from the new expression
    tree.create_tree(expression);
}

// M1: Swap two adjacent operands
std::string NPE::M1()
{
    // variable to contain the starting index which is random
    unsigned int random_index;

    // first index to swap
    unsigned int first_index;

    // second index to swap
    unsigned int second_index;

    // Needed to check if our index is reaching the end of the string
    bool at_end_of_string;
    
    // End expression for the M1 move
    std::string final_expression = expression;

    do
    {
        at_end_of_string = false;

        // random_index is between 0 and expression.size()
        random_index = rd() % expression.size();

        // random_index lands inside a chain
        if(expression[random_index] == 'V' || expression[random_index] == 'H')
        {
            // find the first index outside of the chain
            first_index = expression.find_first_not_of("VH", random_index);
            
            // find the second index outside of the chain
            second_index = expression.find_last_not_of("VH", random_index);

            // Repeat this if the first index is at the end of the string
            if(first_index >= expression.size())
            {
                at_end_of_string = true;
            }
        }

        // random_index lands outside a chain
        else
        {
            first_index = random_index;
            
            // Is the character to the right of the random index an operator?
            if(expression[random_index + 1] == 'V' || expression[random_index + 1] == 'H')
            {
                // Is the character to the left of the random index an operator?
                if(expression[random_index - 1] == 'V' || expression[random_index - 1] == 'H')
                {
                    // Find the next operand after the chain to the right
                    second_index = expression.find_first_not_of("VH", random_index + 1);
                    
                    // Repeat this if the second index is at the end of the string
                    if(second_index >= expression.size())
                    {
                        at_end_of_string = true;
                    }
                }
                // The character to the left of the random index is an operand
                else
                {
                    second_index = first_index - 1;
                }
            }
            // The character to the left of the random index is an operand
            else
            {
                second_index = first_index + 1;
            }
        }
    } while(at_end_of_string);
    
    // Swap the indices
    std::swap(final_expression[first_index], final_expression[second_index]);
    
    return final_expression;
}

// M2: Complement some chain of nonzero length
std::string NPE::M2()
{
    // random_index to find starting point
    unsigned int random_index = rd() % expression.size();

    // place holder for begining of a chain
    unsigned int begin_index;

    std::string final_expression = expression;
    
    // random_index is inside a chain
    if(expression[random_index] == 'V' || expression[random_index] == 'H')
    {
        // This will find the first operator of a chain
        begin_index = expression.find_last_not_of("HV", random_index) + 1;
    }

    // random_index is outside a chain
    else
    {
        // This will find the first operator of a chain
        begin_index = expression.find_first_of("HV", random_index);
    }
    
    // Iterate through the entire chain flipping each operator
    for(unsigned int i = begin_index; i < expression.size() && (expression[i] == 'V' || expression[i] == 'H'); ++i)
    {
        if(final_expression[i] == 'H')
        {
            final_expression[i] = 'V';
        }
        else
        {
            final_expression[i] = 'H';
        }
    }
    return final_expression;
}

// M3: Swap two adjacent operand and operator
// (Need to check if still normailized after swap)
std::string NPE::M3()
{
    // random_index is between 0 and expression.size()
    unsigned int random_index;

    // Check if we are at the end of the string
    bool at_end_of_string;

    // Indices to swap
    unsigned int first_index, second_index;

    // Direction to swap (0 goes to right, 1 goes to left)
    unsigned int direction = rd() % 2;

    // Count to finally give up if no valid swaps are found
    unsigned int count = 0;

    // Final expression to return
    std::string final_expression = expression;
    do
    {
        // check to see if we should give up
        count++;

        if(count > 100)
        {
            return expression;
        }

        at_end_of_string = false;

        // Get a random index
        random_index = rd() % expression.size();
        
        // random_index is inside a chain
        if(expression[random_index] == 'V' || expression[random_index] == 'H')
        {
            // go to right to find end of chain
            if(direction == 0)
            {
                // This will find the last operator of a chain
                first_index = expression.find_first_not_of("HV", random_index) - 1;
                
                // Skip all of at end of string
                if(first_index >= expression.size())
                {
                    at_end_of_string = true;
                }
                // The next index should be an operand
                else
                {
                    second_index = first_index + 1;
                }
            }
            // got to left to find end of chain
            else
            {
                // This will find the first operator of a chain
                first_index = expression.find_last_not_of("HV", random_index) + 1;

                // The previous index should be an operand
                second_index = first_index - 1;
            }
        }
        // random_index is outside a chain
        else
        {
            // go to the right to find a beginning of a chain
            if(direction == 0)
            {
                // This will be the first operator of a chain
                first_index = expression.find_first_of("HV", random_index);

                // This previous index should be an operand
                second_index = first_index - 1;
            }
            // go to the left to find a ending of a chain
            else
            {
                // This will find the end of a chain
                first_index = expression.find_last_of("HV", random_index);
                
                // Skip all of at end of string
                if(first_index >= expression.size())
                {
                    at_end_of_string = true;
                }
                // The next index should be an operand
                else
                {
                    second_index = first_index + 1;
                }
            }
        }

    } while(!verify(first_index, second_index) || at_end_of_string );

    std::swap(final_expression[first_index], final_expression[second_index]);

    return final_expression;
}

bool NPE::verify(unsigned int first, unsigned int second)
{
    // initial check
    if(first > expression.size())
    {
        return false;
    }

    // Variable to hold the number of operands
    unsigned int operand_count = 0;
    
    // Variable to hold the number of operators
    unsigned int operator_count = 0;

    // String to test the swap
    std::string test = expression;

    // Swap the first and second indices
    std::swap(test[first], test[second]);

    // Move through the string to make sure that the changes
    // still produce an NPE
    for(unsigned int i = 0; i < test.size(); ++i)
    {
        // Checks for repeated operators
        if(i + 1 < test.size() && (test[i] == test[i + 1]))
        {
            return false;
        }

        // Checks if the balloting condition is satisfied
        if(test[i] == 'V' || test[i] == 'H')
        {
            operator_count++;
        }
        else
        {
            operand_count++;
        }
        
        if(operator_count >= operand_count)
        {
            return false;
        }
    }
    return true;
}

void NPE::print_tree()
{
    tree.display_tree();
}

double NPE::cost()
{
    return tree.cost();
}

int NPE::get_number_of_operands()
{
    int total = 0;
    for(unsigned int i = 0; i < expression.size(); ++i)
    {
        if(expression[i] != 'V' && expression[i] != 'H')
        {
            total++;
        }
    }
    return total;
}
