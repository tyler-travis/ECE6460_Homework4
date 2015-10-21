// File: operand_node.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include "operand_node.hpp"


operand_node::operand_node()
    : node()
{
    aspect_ratio = 0;
    area = 0;
    length = 0;
    width = 0;
}

operand_node::operand_node(std::string _op, double _aspect_ratio, double _area)
    : node()
{
    name = _op;
    aspect_ratio = _aspect_ratio;
    area = _area;
    set_length_width();
}

void operand_node::set_length_width()
{
    length = sqrt(area/aspect_ratio);
    width = aspect_ratio*length;
    // Clear the dimensions vector before setting new lengths and widths
    if(!v_dimensions.empty())
    {
        v_dimensions.clear();
    }
    v_dimensions.push_back(std::pair<double, double>(length, width));
    v_dimensions.push_back(std::pair<double, double>(width, length));
}

operand_node::operand_node(const operand_node& copy_node)
    : node(copy_node)
{
    this->aspect_ratio = copy_node.aspect_ratio;
    this->area = copy_node.area;
    this->width = copy_node.width;
    this->length = copy_node.length;
}

void operand_node::set_aspect_ratio(double _aspect_ratio)
{
    aspect_ratio = _aspect_ratio;
    set_length_width();
}

void operand_node::set_area(double _area)
{
    area = _area;
    set_length_width();
}

double operand_node::get_aspect_ratio()
{
    return aspect_ratio;
}

double operand_node::get_area()
{
    return area;
}
