// File: main.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include <cstdlib>
#include <random>
#include "NPE.hpp"

int main(int argc, char** argv)
{
    NPE npe1("input_file.txt");
    std::string temp;
    std::random_device rd;
    int rnum;
    std::string original = npe1.get_NPE();
    //npe1.set_NPE("123H456HV78VHVH");
    //std::cout << "NPE: " << npe1.get_NPE() << std::endl;
    //std::cout << "M1:  " << npe1.M1() << std::endl;
    //std::cout << "M2:  " << npe1.M2() << std::endl;
    //std::cout << "M3:  " << npe1.M3() << std::endl;
    for(int i = 0; i < 10000; ++i)
    {
        //std::cout << "----------------------------------------------" << std::endl;
        rnum = rd() % 3 + 1;
        //std::cout << rnum << std::endl;
        switch(rnum)
        {
            case 1:
                temp = npe1.M1();
                if(temp.size() < original.size())
                {
                    std::cout << "1" << std::endl;
                    break;
                }
                npe1.set_NPE(temp);
                break;
            case 2:
                temp = npe1.M2();
                if(temp.size() < original.size())
                {
                    std::cout << "2" << std::endl;
                    break;
                }
                npe1.set_NPE(temp);
                break;
            case 3:
                temp = npe1.M3();
                if(temp.size() < original.size())
                {
                    std::cout << "3" << std::endl;
                    break;
                }
                npe1.set_NPE(temp);
                break;
            default:
                std::cout << "What?" << std::endl;
        }
        //std::cout << "M" << rnum << ": " << npe1.get_NPE() << std::endl;
    }
    std::cout << "initi NPE: " << original << std::endl;
    std::cout << "final NPE: " << npe1.get_NPE() << std::endl;
    //std::cout << "NPE size: " << npe1.get_NPE().size() << std::endl;
    //std::cout << "original NPE size: " << original.size() << std::endl;
    npe1.print_tree();
    return 0;
}
