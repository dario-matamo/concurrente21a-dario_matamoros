// Copyright 2021 Donaldo Salas-Loria, Dario Matamoros, Manfred Carvajal
#include <iostream>
#include <omp.h>
#include <mpi.h>
#include <chrono>
#include <fstream>
#include "GoldbachCalculator.hpp"

using namespace std;



int main(int argc, char* argv[]) {
  auto start = chrono::steady_clock::now();
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    //Initialices all the values needed to use MPI
    int rank = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processCount = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    //Vector with the numbers to solve
    std::vector<int>*numbersToSolve = new std::vector<int>();
    int arraySize = 0;
    int* numbersPtr;
    int canPrint;
    MPI_Status status;
    //If the is the first process reads the numbers to send to the
    //other process
    if(rank==0){
      int64_t number;
      while(std::cin>>number){
        numbersToSolve->push_back(number);  
      }
      arraySize = numbersToSolve->size();
      numbersPtr = new int [arraySize];
      for(int i = 0;i<arraySize; i++){
        numbersPtr[i]=numbersToSolve->at(i);
      }
    }
    //Sends the array size 
    MPI_Bcast(&arraySize,1,MPI_INT,0,MPI_COMM_WORLD);
   if(rank != 0) {
       numbersPtr = new int [arraySize];
   }
   MPI_Bcast(numbersPtr,arraySize,MPI_INT,0,MPI_COMM_WORLD);

    GoldbachController* controller = new GoldbachController(rank, processCount);
    
    for(int i = 0;i<arraySize; i++){
      numbersToSolve->push_back(numbersPtr[i]);
    }
    // Creates the start index and finish index to do the block
    std::vector<GoldbachCalculator*>*solvedNumbers = new std::vector<GoldbachCalculator*>();
    int startBlock = controller->calculateFirstIndex(controller->getProcessRank(),
    arraySize, controller->getProcessCount());
    int finishBlock = controller->calculateLastIndex(controller->getProcessRank(),
    arraySize, controller->getProcessCount());
    //Does the concurrency with OMP
    #pragma omp parallel for num_threads(3) default(none) \
    shared(numbersToSolve,cout,solvedNumbers,startBlock,finishBlock) schedule(dynamic)
    for (int i = startBlock; i <finishBlock; ++i){
      if (i<numbersToSolve->size()) {
        GoldbachCalculator* cal = new GoldbachCalculator(numbersToSolve->at(i));
        cal->calculateGoldbach(numbersToSolve->at(i));
        solvedNumbers->push_back(cal);
      }
    }
    
    // Prints the sums syncronizing the processes
    if (rank == 0) {
    for (size_t i = 0; i < solvedNumbers->size(); i++)
    {
      solvedNumbers->at(i)->printGolbachSums();
    }
    MPI_Send(&canPrint, 1, MPI_INT, 1, 2020, MPI_COMM_WORLD);
    }
  if (rank > 0) {
    MPI_Recv (&canPrint, 1, MPI_INT, rank - 1, 2020, MPI_COMM_WORLD, &status);
    for (size_t i = 0; i < solvedNumbers->size(); i++) {
      solvedNumbers->at(i)->printGolbachSums();
    }
    if (rank < processCount - 1) {
      MPI_Send(&canPrint, 1, MPI_INT, rank + 1, 2020, MPI_COMM_WORLD);
    }
  }
   MPI_Finalize();
  }
  auto end = chrono::steady_clock::now();
  cout << "Elapsed time in seconds: "
  << chrono::duration_cast<chrono::seconds>(end - start).count()
  << " sec";
  return 0;
}
