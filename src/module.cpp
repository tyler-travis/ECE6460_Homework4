// File: module.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include "module.hpp"

module::module()
{
    name = "";
    area = 0;
    aspect_ratio = 0;
}

module::module(std::string _name, double _area, double _aspect_ratio)
{
    name = _name;
    area = _area;
    aspect_ratio = _aspect_ratio;
}


std::string module::get_name()
{
    return name;
}

double module::get_area()
{
    return area;
}

double module::get_aspect_ratio()
{
    return aspect_ratio;
}


void module::set_name(std::string _name)
{
    name = _name;
}

void module::set_area(double _area)
{
    area = _area;
}

void module::set_aspect_ratio(double _aspect_ratio)
{
    aspect_ratio = _aspect_ratio;
}

