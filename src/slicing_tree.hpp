// File: slicing_tree.hpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#ifndef SLICING_TREE_HPP
#define SLICING_TREE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <algorithm>

#include "module.hpp"
#include "node.hpp"
#include "operand_node.hpp"
#include "operator_node.hpp"

typedef std::vector<std::pair<double, double> > dimension_list;
typedef std::pair<double, double> dimension;

class slicing_tree
{
    private:
        // Root of the tree
        node* root;

        // List of the module parameters
        std::vector<module> module_list;

        // The NPE used for the slicing tree
        std::string NPE;

        int create_tree(node*, std::string, int);
        void display_tree(node*, int);
        void display_tree_post_order(node*);
        void display_tree_dimensions(node*);
        void populate_dimension_lists();
        dimension_list populate_dimension_lists(node*);
        dimension_list delete_maximums(dimension_list);

    public:
        slicing_tree();
        // Create a tree based on an NPE
        void create_tree(std::string);

        // Import the module list
        void import_module_list(std::string);

        // Show the module list
        void display_module_list();

        // Display the tree in a tree pattern
        void display_tree();

        // List all the nodes with their dimensions
        void display_tree_dimensions();

        // Display the tree in post_order
        void display_tree_post_order();

        // Find the cost of the slicing tree
        double cost(std::string);
};

#endif
