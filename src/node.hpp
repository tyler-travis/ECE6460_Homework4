// File: node.hpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <utility>
#include <string>

class node
{
    protected:
        // Pointer to left child
        node* p_left;

        // Pointer to right child
        node* p_right;

        // Pointer to the parent
        node* p_parent;

        // vector for storing possible dimension orientations
        std::vector<std::pair<double, double> > v_dimensions;

        std::string name;

    public:
        // Default constructor
        node();

        // set left and right pointer constructor
        node(node*, node*);

        node(const node&);

        // set name
        void set_name(std::string);

        // Set the left pointer
        void set_left(node*);

        // Set the right pointer
        void set_right(node*);

        // Set the parent pointer
        void set_parent(node*);

        // Put a new dimension into the dimension array
        void set_dimension(std::pair<double, double>);
        
        // Set dimension list
        void set_dimension_list(std::vector<std::pair<double, double> >);

        // Get name
        std::string get_name();

        // Get the left pointer
        node* get_left();

        // Get the right pointer
        node* get_right();

        // Get the parent pointer
        node* get_parent();

        // Get the dimension at a certain index
        std::pair<double, double> get_dimension(unsigned int);

        // Get a copy of the dimension list
        std::vector<std::pair<double, double> > get_dimension_list();

        // Remove a dimension at a certain index
        bool remove_dimension(unsigned int);
};

#endif
