#include "GoldbachCalculator.hpp"
GoldbachCalculator::GoldbachCalculator(int64_t goldbach_number){
    this->goldbach_number = goldbach_number;
    this->queue_solutions = new std::vector<int64_t>();
}

GoldbachCalculator::GoldbachCalculator(){
    this->goldbach_number = 0;
    this->queue_solutions = new std::vector<int64_t>();
}

GoldbachCalculator::~GoldbachCalculator(){
    //delete this->goldbach_number;
    delete this->queue_solutions;
    
}
std::vector<int64_t>* GoldbachCalculator::getQueue(){
    return this->queue_solutions;    
}
void GoldbachCalculator::calculateGoldbach(int64_t number){
    size_t typeGolbach = number%2;
    if (typeGolbach == 0) {
        strongConjecture(number);
    } else {
		weakConjecture(number); 
    }
}
int GoldbachCalculator::getCantitySums(){
    if(labs((this->goldbach_number%2))==1){
        return this->queue_solutions->size()/3;
    }else{
        return this->queue_solutions->size()/2;
    }
}
void GoldbachCalculator::strongConjecture(int64_t number){
    number = labs(number);
    for (int64_t i=2; i <= number/2; i++) {
        if (isPrime(i) == 1 && isPrime(number-i) == 1) {
           this->queue_solutions->push_back(i);
           this->queue_solutions->push_back(number-i);
        }
    }
}
void GoldbachCalculator::weakConjecture(int64_t number){
    number = labs(number);
    for (int64_t i = 0; i < number; i++) {
        for (int64_t j = i; j < number; j++) {
            for (int64_t k = j; k < number; k++) {
                    // Checks if the sum of the 3 iterations equals the number
                if (i + j + k == number ) {
                        // Appends the primes to the list to be printed later
                    if(isPrime(i)==1 && isPrime(j)==1 &&isPrime(k)==1){
                        queue_solutions->push_back(i);
                        queue_solutions->push_back(j);
                        queue_solutions->push_back(k);
                    }
                }
            }
        }
    }
}      
bool GoldbachCalculator::isPrime(int64_t number){
   bool prime = true;
    if (number <= 1) {
		prime = false;
    } else {
        for (int64_t i=2; i<=sqrt(number); i++) {
             if (number % i == 0) {
			     prime = false;
             }
        }
    }
    return prime;
}
int64_t GoldbachCalculator::getGoldbachNumber(){
    return this->goldbach_number;
}
void GoldbachCalculator::setGoldbachNumber(int64_t number){
    this->goldbach_number=number;
}