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
    tree.import_module_list(fileName);
    std::string temp = tree.get_module_names();

    if(!expression.empty())
    {
        expression.clear();
    }
    expression.push_back(temp[0]);
    for(unsigned int i = 1; i < temp.size(); ++i)
    {
        expression.push_back(temp[i]);
        expression.push_back('V');
    }
}


const std::string NPE::get_NPE(void)
{
    return expression;
}

std::string NPE::M1()
{
    bool valid_swap = false;
    unsigned int rand_index;
    unsigned int swap_index;
    std::string return_expression = expression;

    while(!valid_swap)
    {
        rand_index = rd() % expression.size();
        while(expression[rand_index] == 'V' || expression[rand_index] == 'V')
        {
            rand_index++;
            if(rand_index >= expression.size())
            {
                rand_index = 0;
            }
        }
        swap_index = rand_index + 1;
        while(expression[swap_index] == 'V' || expression[swap_index] == 'H')
        {
            swap_index++;
            if(swap_index >= expression.size())
            {
                valid_swap = false;
            }
            else
            {
                valid_swap = true;
            }
        }
    }
    std::cout << "rand: " << rand_index << std::endl;
    std::cout << "swap: " << swap_index << std::endl;
    std::swap(return_expression[rand_index], return_expression[swap_index]);
    return return_expression;
}

// M2: Complement some chain of nonzero length
std::string NPE::M2()
{
    std::string return_expression = expression;
    unsigned int starting_index = rd() % expression.size();
    // If in the middle of a chain, find the beginning
    while(expression[starting_index] == 'V' || expression[starting_index] == 'H')
    {
        starting_index--;
    }
    starting_index++;

    // Take the complement of this chain
    while(expression[starting_index] == 'V' || expression[starting_index] == 'H')
    {
        if(expression[starting_index] == 'V')
        {
            return_expression[starting_index] = 'H';
        }
        else if(expression[starting_index] == 'H')
        {
            return_expression[starting_index] = 'V';
        }
        if(starting_index > expression.size())
        {
            break;
        }
        starting_index++;
    }
    return return_expression;

}

// M3: Swap two adjacent operand and operator
// (Need to check if still normailized after swap)
// TODO: What to do if end of string?
std::string NPE::M3()
{
    std::string return_expression = expression;
    unsigned int rand_index = rd() % expression.size();
    if(expression[rand_index] != 'V' && expression[rand_index] != 'H')
    {
        while(expression[rand_index + 1] != 'V' && expression[rand_index + 1] != 'H')
        {
            rand_index++;
        }
        std::swap(return_expression[rand_index], return_expression[rand_index + 1]);
    }
    else if(expression[rand_index] == 'V' || expression[rand_index] == 'H')
    {
        while(expression[rand_index + 1] == 'V' || expression[rand_index + 1] == 'H')
        {
            rand_index++;
        }
        std::swap(return_expression[rand_index], return_expression[rand_index + 1]);
    }
    return return_expression;
}

