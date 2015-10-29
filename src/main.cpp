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

    // Define the initial cost of the initial expression
    double init_cost = E_0.cost();
    std::cout << "Initial NPE:  " << E_0.get_NPE() << std::endl;
    std::cout << "Initial Cost: " << init_cost << std::endl;

    // A vector to determine the average cost of an uphill move
    std::vector<double> costs;

    double total = 0;
    for(unsigned int i = 0; i < 100; ++i)
    {
        // Pick a random move
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
        // Set a new expression as the result of the move
        del_avg_NPE.set_NPE(temp);
        
        // Calculate the cost
        double cost = del_avg_NPE.cost();

        // Only accept the move if the cost is greater than the initial cost
        if(cost > init_cost)
        {
            costs.push_back(cost - init_cost);
        }
    }

    // Calculate the average
    for(unsigned int i = 0; i < costs.size(); ++i)
    {
        total += costs[i];
    }

    double del_avg = total/costs.size();

    // Determine the initial temperature to use
    double T_0 = -del_avg/log(0.99);

    double T = T_0;

    // reject - number of moves rejected by the algorithm in one iteration
    // MT     - number of moves by the algorithm in one iteration
    // uphill = number of uphill moves accepted by the algorithm in one interation
    int reject, MT, uphill;

    // number of moves per module
    int nmoves = 10;

    // number of modules 
    int n = E_0.get_number_of_operands();

    // number of moves per module per iteration
    int N = nmoves * n;

    // The ratio of each iterative temperature
    double ratio = 0.85;

    // Once temperature is below epsilon, the algorithm stops
    double epsilon = 0.001;

    // Once temperature is below lambdatf * T_0 decrease the ratio to 0.1
    double lambdatf = 0.005;

    // A variable to check to see if ratio has changed
    bool changed = false;

    // Start of the alrogrithm
    do
    {
        // Reset variables
        reject = 0;
        MT = 0;
        uphill = 0;

        do
        {
            // Find a random move to do
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

            // Set the new NPE
            newE.set_NPE(temp);

            // Increment the number of moves
            MT++;

            // Find the differenct of the new cost and current cost
            double del_cost = newE.cost() - E.cost();

            // Get a random number between 0 and 1
            double random = ((double) rand() / (RAND_MAX));
            
            // Accept the move if the cost is better
            // OR
            // We random decide to accept an uphill move
            if(del_cost < 0 || random < exp(-del_cost/T))
            {
                // If the cost isn't better increment the uphill variable
                if(del_cost > 0)
                {
                    uphill++;
                }

                // Officially accept the move
                E.set_NPE(newE.get_NPE());

                // If this is the best cost seen so far accept it as best
                if(E.cost() < Best.cost())
                {
                    Best.set_NPE(E.get_NPE());
                }
            }
            // Reject the move
            else
            {
                reject++;
            }
            // Contune to do this as long as the number of uphill moves is <= N
            // and the number of moves is <= 2*N
        } while(uphill <= N && MT <= 2*N);

        // Check to see if we have changed the ratio
        // And see if we need to change the ratio
        if(!changed && T < lambdatf * T_0)
        {
            changed = true;
            ratio = 0.1;
        }
        // calculate the new temperature for this iteration
        T = ratio*T;

        // Repeat this while the ratio of rejecting to moves made is greater than 95%
        // AND
        // The temperature is greater than epsilon (0.001)
    } while(reject/MT <= 0.95 && T > epsilon);

    // Display the best topology and the cost of that topology
    std::cout << "Best NPE:  " << Best.get_NPE() << std::endl;
    std::cout << "Best Cost: " << Best.cost() << std::endl;
}
