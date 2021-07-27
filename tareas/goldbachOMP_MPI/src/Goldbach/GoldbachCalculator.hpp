#ifndef GOLDBACHCALCULATOR_H
#define GOLDBACHCALCULATORP_H
#include "Queue.hpp"
#include <vector>
#include <cmath>
#include "GoldbachController.hpp"
using namespace std;
class GoldbachCalculator{
    private:
        int64_t goldbach_number;
        std::vector<int64_t>* queue_solutions;
    protected:
    public:
    /**
    * @brief: Goldbach calculator destructor
    */
    ~GoldbachCalculator();
    /**
    * @brief: Goldbach calculator constructor
    * @param: number to which the sums are to be calculated
    */
    GoldbachCalculator(int64_t goldbach_number);
    //Constructor vacio
    GoldbachCalculator();
    /**
    * @brief: Goldbach calculator destructor
    */
    /**
    * @brief: calls methods to find goldbach sums depending if it is even or odd
    * @param: number to which the sums are to be calculated
    * @return: Returns void
    */ 
    void calculateGoldbach(int64_t number);
    /**
    * @brief: Determines if a number is prime 
    * @param: An int number to determine if it is prime
    * @return: Returns a bool, if it is prime true, else false
    */ 
    bool isPrime(int64_t number);
    /**
    * @brief: Finds all Goldbach sums of an even number
    * @param: number to which the sums are to be calculated
    * @return: Returns void
    */
    void strongConjecture(int64_t number);
    /**
    * @brief: Finds all Goldbach sums of an odd number
    * @param: number to which the sums are to be calculated
    * @return: Returns void
    */ 
    void weakConjecture(int64_t number);
    /**
    * @brief: Returns the queue where the results are stored
    * @return: Returns pointer to the queue
    */ 
    std::vector<int64_t>* getQueue();
    /**
    * @brief: Gets total of Goldbach sums of a number
    * @return: Returns an int number, total sums of a number
    */ 
    int getCantitySums();

    int64_t getGoldbachNumber();

    void setGoldbachNumber(int64_t number);

    void printGolbachSums();

    void printStrongConjecture();

    void printWeakConjecture();
};
#endif
