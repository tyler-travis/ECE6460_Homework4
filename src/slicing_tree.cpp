// File: slicing_tree.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include "slicing_tree.hpp"

slicing_tree::slicing_tree()
{
    root = new node();
}

void slicing_tree::create_tree(std::string _NPE)
{
    NPE = _NPE;
    create_tree(root, _NPE, _NPE.size() - 1);
}

int slicing_tree::create_tree(node* current_node, std::string _NPE, int index)
{
    if(index < 0)
    {
        return -1;
    }
    // Get the current letter to analyze
    std::string name(1, _NPE[index]);

    // Determine if it is a operator or an operand
    // operands are either H or V
    // operators are everything else
    if(name == "H" || name == "V")
    {
        // Define a new operator node
        *current_node = operator_node(name);

        // Set it equal to the root if there isn't anything set to root
        if(root == 0)
        {
            root = current_node;
        }

        // Create the new children nodes
        current_node->set_right(new node);
        current_node->set_left(new node);

        // Go do the tree to make the new nodes and tree structure
        index = create_tree(current_node->get_right(), _NPE, index-1);
        current_node->get_right()->set_parent(current_node);
        index = create_tree(current_node->get_left(), _NPE, index-1);
        current_node->get_left()->set_parent(current_node);
        return index;
    }
    else
    {
        // Set up the operand node from the module list setting the aspect ratio
        // and the area of the specific node
        for(unsigned int i = 0; i < module_list.size(); ++i)
        {
            if(module_list[i].get_name() == name)
            {
                *current_node = operand_node(module_list[i].get_name(), 
                        module_list[i].get_aspect_ratio(), module_list[i].get_area());
                return index;
            }
        }
    }
    return 0;
}

void slicing_tree::import_module_list(std::string input_file)
{
    // Import the module list from the corresponding file
    std::ifstream fin(input_file.c_str());
    std::string temp_name;
    double temp_area;
    double temp_aspect_ratio;
    while(fin >> temp_name)
    {
        fin >> temp_area;
        fin >> temp_aspect_ratio;
        module_list.push_back(module(temp_name, temp_area, temp_aspect_ratio));
    }
}

void slicing_tree::display_module_list()
{
    // Display the module list
    std::cout << "M O D U L E    L I S T" << std::endl;
    for(unsigned int i = 0; i < module_list.size(); ++i)
    {
        std::cout << module_list[i].get_name() << "\t"
            << module_list[i].get_area() << "\t"
            << module_list[i].get_aspect_ratio() << "\t"
            << sqrt(module_list[i].get_area()/module_list[i].get_aspect_ratio()) << " x "
            << sqrt(module_list[i].get_area()/module_list[i].get_aspect_ratio()) * module_list[i].get_aspect_ratio()
            << std::endl;
    }
}

void slicing_tree::display_tree()
{
    display_tree(root, 0);
}

void slicing_tree::display_tree(node* current_node, int space)
{
    // This is a recursive function to display the tree in a tree
    // like pattern
    if(current_node != 0)
    {
        if(current_node->get_right())
        {
            display_tree(current_node->get_right(), space+4);
        }
        for(int i = 0; i < space; ++i)
        {
            std::cout << " ";
        }
        std::cout << current_node->get_name() << std::endl;
        if(current_node->get_left())
        {
            display_tree(current_node->get_left(), space+4);
        }
    }
}

void slicing_tree::display_tree_post_order()
{
   display_tree_post_order(root); 
   std::cout << std::endl;
}

void slicing_tree::display_tree_post_order(node* current_node)
{
    // Displays the tree in post order
    if(current_node == 0)
    {
        return;
    }
    
    display_tree_post_order(current_node->get_left());
    display_tree_post_order(current_node->get_right());
    std::cout << current_node->get_name();
}

void slicing_tree::display_tree_dimensions()
{
    display_tree_dimensions(root);
}

void slicing_tree::display_tree_dimensions(node* current_node)
{
    // Displays the node with the corresponding dimensions at that node
    if(current_node == 0)
    {
        return;
    }
    
    display_tree_dimensions(current_node->get_left());
    display_tree_dimensions(current_node->get_right());
    std::cout << current_node->get_name();
    std::cout << ": ";
    for(unsigned int i = 0; i < current_node->get_dimension_list().size(); ++i)
    {
        std::cout << "(" <<  current_node->get_dimension_list()[i].first << " x "
            << current_node->get_dimension_list()[i].second
            << "), ";
    }
    std::cout << std::endl << "------------------------------------------------------------------------------------------------" << std::endl;
}

double slicing_tree::cost(std::string _NPE)
{
    // Create the tree corrisponding to the NPE
    create_tree(_NPE);
    
    // Populate the tree with all the proper dimensions
    populate_dimension_lists();

    // Get all of the dimensions at the root node
    dimension_list root_list = root->get_dimension_list();
    double minimum_area = root_list[0].first * root_list[0].second;
    double area;

    // Find the smallest area at the root node
    for(unsigned int i = 0; i < root_list.size(); ++i)
    {
        area = root_list[i].first * root_list[i].second;
        if(area < minimum_area)
        {
            minimum_area = area;
        }
    }
    
    // return the minimum area
    return minimum_area;
}

void slicing_tree::populate_dimension_lists()
{
    populate_dimension_lists(root);
}

dimension_list slicing_tree::populate_dimension_lists(node* current_node)
{
    // check if it is a leaf node (aka operand node)
    if(current_node->get_name() != "V" && current_node->get_name() != "H")
    {
        // Return the current nodes dimension list
        return current_node->get_dimension_list();
    }
    else
    {
        // Get the left and right tree's dimension lists
        double total_width, total_length;
        dimension_list current_dimension_list_right = populate_dimension_lists(current_node->get_right());
        dimension_list current_dimension_list_left = populate_dimension_lists(current_node->get_left());
        dimension_list current_dimension_list_final;
        
        // If the operator is a "V", add the widths together and take the max height for the combined dimension
        // Do this for every combination of dimensions in the two lists
        if(current_node->get_name() == "V")
        {
            for(unsigned int i = 0; i < current_dimension_list_right.size(); ++i)
            {
                for(unsigned int j = 0; j < current_dimension_list_left.size(); ++j)
                {
                    double width_right = current_dimension_list_right[i].first;
                    double width_left = current_dimension_list_left[j].first;

                    double length_right = current_dimension_list_right[i].second;
                    double length_left = current_dimension_list_left[j].second;
                    total_width = width_right + width_left;
                    total_length = std::max(length_right, length_left);
                    current_dimension_list_final.push_back(std::pair<double, double>(total_width, total_length));
                }
            }
        }
        // If the operator is a "H", add the lengths together and take the max widths for the combined dimension
        // Do this for every combination of dimensions in the two lists
        else
        {
            for(unsigned int i = 0; i < current_dimension_list_right.size(); ++i)
            {
                for(unsigned int j = 0; j < current_dimension_list_left.size(); ++j)
                {
                    double width_right = current_dimension_list_right[i].first;
                    double width_left = current_dimension_list_left[j].first;

                    double length_right = current_dimension_list_right[i].second;
                    double length_left = current_dimension_list_left[j].second;

                    total_length = length_right + length_left;
                    total_width = std::max(width_left, width_right);
                    current_dimension_list_final.push_back(std::pair<double, double>(total_width, total_length));
                }
            }
        }
        // Delete some dimensions that are bigger than others
        current_dimension_list_final = delete_maximums(current_dimension_list_final);

        // Update the current node to contain the current dimension list
        for(unsigned int i = 0; i < current_dimension_list_final.size(); ++i)
        {
            current_node->set_dimension_list(current_dimension_list_final);
        }
        return current_dimension_list_final;
    }
}

dimension_list slicing_tree::delete_maximums(dimension_list list)
{
    // Vector to contain a list of all indices to delete
    std::vector<unsigned int> indices_to_delete;

    // Go through each element and comapre it agains itself
    for(unsigned int i = 0; i < list.size(); ++i)
    {
        for(unsigned int j = 0; j < list.size(); ++j)
        {
            // Don't delete the same index
            if(i == j)
            {
                continue;
            }
            // If they are the same, don't delete
            else if(list[i].first == list[j].first && list[i].second == list[j].second)
            {
                continue;
            }
            else
            {
                // Mark to delete only if BOTH width and height are bigger
                if(list[i].first <= list[j].first && list[i].second <= list[j].second)
                {
                    indices_to_delete.push_back(j);
                }
            }
        }
    }
    // Sort the indicies to delete
    std::sort(indices_to_delete.begin(), indices_to_delete.end());

    // check to make sure all indicies are unique in the vector
    std::vector<unsigned int>::iterator it;
    it = std::unique(indices_to_delete.begin(), indices_to_delete.end());

    // Resize the vector
    indices_to_delete.resize(std::distance(indices_to_delete.begin(), it));

    // Delete the indicies marked to delete
    for(unsigned int i = 0; i < indices_to_delete.size(); ++i)
    {
        list.erase(list.begin() + indices_to_delete[i]-i);
    }
    return list;
}
