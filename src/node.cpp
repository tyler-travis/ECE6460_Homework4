// File: node.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include "node.hpp"

node::node()
{
    p_right = 0;
    p_left = 0;
    p_parent = 0;
    v_dimensions = std::vector<std::pair<double,double> >(10);
}

node::node(const node& copy_node)
{
    this->p_right = copy_node.p_right;
    this->p_left = copy_node.p_left;
    this->p_parent = copy_node.p_parent;
    this->name = copy_node.name;
    this->v_dimensions = copy_node.v_dimensions;
}

void node::set_name(std::string _name)
{
    name = _name;
}
// Set the left pointer
void node::set_left(node* _p_left)
{
    p_left = _p_left;
}

// Set the right pointer
void node::set_right(node* _p_right)
{
    p_right = _p_right;
}

// Set the parent pointer
void node::set_parent(node* _p_parent)
{
    p_parent = _p_parent;
}

// Put a new dimension into the dimension array
void node::set_dimension(std::pair<double, double> _dimension)
{
    v_dimensions.push_back(_dimension);
}

std::string node::get_name()
{
    return name;
}

// Get the left pointer
node* node::get_left()
{
    return p_left;
}

// Get the right pointer
node* node::get_right()
{
    return p_right;
}

// Get the parent pointer
node* node::get_parent()
{
    return p_parent;
}

// Get the dimension at a certain index
std::pair<double, double> node::get_dimension(unsigned int _index)
{
    return v_dimensions[_index];
}

std::vector<std::pair<double, double> > node::get_dimension_list()
{
    return v_dimensions;
}

bool node::remove_dimension(unsigned int _index)
{
    if (_index > v_dimensions.size())
    {
        return false;
    }
    // Delete the element at the beginning + the index
    // Effectively like: dimensions.delete(_index);
    v_dimensions.erase(v_dimensions.begin() + _index);
    return true;
}

void node::set_dimension_list(std::vector<std::pair<double, double> > list)
{
    v_dimensions = list;
}
