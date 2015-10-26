// File: main.cpp
// Author: Tyler Travis
// A#: A01519795
// Homework 3

#include <cstdlib>
#include <random>
#include <cmath>
#include "NPE.hpp"

void Simulated_Annealing();

int main(int argc, char** argv)
{
    Simulated_Annealing();
    return 0;
}

void Simulated_Annealing()
{
    // Initialize random number to seed 3
    srand(3);

    // Initialize the various components of the algorithm
    NPE E_0("input_file.txt");
    NPE E("input_file.txt", E_0.get_NPE());
    NPE Best("input_file.txt", E_0.get_NPE());
    NPE newE("input_file.txt");

    // NPE for finding the average cost gain of moves
    NPE del_avg_NPE("input_file.txt", E_0.get_NPE());

    double init_cost = E_0.cost();
    std::cout << "Initial NPE:  " << E_0.get_NPE() << std::endl;
    std::cout << "Initial Cost: " << init_cost << std::endl;

    std::vector<double> costs;

    double total = 0;
    for(unsigned int i = 0; i < 100; ++i)
    {
        int move = rand() % 3 + 1;
        std::string temp;
        switch(move)
        {
            case 1:
                temp = E_0.M1();
                break;
            case 2:
                temp = E_0.M2();
                break;
            case 3:
                temp = E_0.M3();
                break;
        }
        del_avg_NPE.set_NPE(temp);
        double cost = del_avg_NPE.cost();
        if(cost > init_cost)
        {
            costs.push_back(cost - init_cost);
        }
    }

    for(unsigned int i = 0; i < costs.size(); ++i)
    {
        total += costs[i];
    }

    double del_avg = total/costs.size();

    double T_0 = -del_avg/log(0.99);

    double T = T_0;

    int reject, MT, uphill;

    int nmoves = 10;

    int n = E_0.get_number_of_operands();

    int N = nmoves * n;

    double ratio = 0.85;

    double epsilon = 0.001;

    double lambdatf = 0.005;

    bool changed = false;

    do
    {
        reject = 0;
        MT = 0;
        uphill = 0;

        do
        {
            int move = rand() % 3 + 1;
            std::string temp;

            switch(move)
            {
                case 1:
                    temp = E.M1();
                    break;

                case 2:
                    temp = E.M2();
                    break;

                case 3:
                    temp = E.M3();
                    break;

                default:
                    std::cout << "Something weird happened" << std::endl;
            }
            newE.set_NPE(temp);

            MT++;

            double del_cost = newE.cost() - E.cost();
            //std::cout << "del_cost: " << del_cost << std::endl;

            double random = ((double) rand() / (RAND_MAX));
            //std::cout << "random: " << random << std::endl;
            //std::cout << "exp(-del_cost/T): " << exp(-del_cost/T) << std::endl;
            
            if(del_cost < 0 || random < exp(-del_cost/T))
            {
                if(del_cost > 0)
                {
                    uphill++;
                }
                E.set_NPE(newE.get_NPE());
                if(E.cost() < Best.cost())
                {
                    Best.set_NPE(E.get_NPE());
                }
            }
            else
            {
                reject++;
            }
            //std::cout << "MT: " << MT << std::endl;
            //std::cout << "Moving" << std::endl;
        } while(uphill <= N && MT <= 2*N);
        if(!changed && T < lambdatf * T_0)
        {
            changed = true;
            ratio = 0.1;
        }
        else
        {
            T = ratio*T;
        }
    } while(reject/MT <= 0.95 && T > epsilon);
    std::cout << "Best NPE:  " << Best.get_NPE() << std::endl;
    std::cout << "Best Cost: " << Best.cost() << std::endl;
}
