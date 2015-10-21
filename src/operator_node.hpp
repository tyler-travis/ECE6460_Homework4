// File: operator_node.hpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#ifndef OPERATOR_NODE_HPP
#define OPERATOR_NODE_HPP

#include "node.hpp"
#include <string>

class operator_node: public node
{
    // name should either be H or V
    // H - horizontal cut
    // V - Vertical cut

    public:
        operator_node();
        operator_node(std::string);

};

#endif

