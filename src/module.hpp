// File: module.hpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#ifndef MODULE_HPP
#define MODULE_HPP

#include <string>

class module
{
    private:
        std::string name;
        double area;
        double aspect_ratio;
    public:
        module();
        module(std::string, double, double);

        std::string get_name();
        double get_area();
        double get_aspect_ratio();

        void set_name(std::string);
        void set_area(double);
        void set_aspect_ratio(double);
};

#endif
