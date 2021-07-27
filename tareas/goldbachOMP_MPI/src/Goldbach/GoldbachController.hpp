using namespace std;
#include <iostream>
class GoldbachController{
    private:
    int processRank;
    int processCount;
   
    public:
    GoldbachController(int processRank, int processCount);
    /**
    * @brief Calculates the index to start index for each process
    * @param rank Rank of the process
    * @param arraySize Size of the array to work in
    * @param processCount Cantity of process
    * @return start of the block to work in
    */
    int calculateFirstIndex(int rank, int arraySize
    , int processCount);
    /**
    * @brief Calculates the index to end last index for each process
    * @param rank Rank of the process
    * @param arraySize Size of the array to work in
    * @param processCount Cantity of process
    * @return end of the block to work in
    */
    int calculateLastIndex(int rank, int arraySize
    , int processCount);
    int getProcessCount();
    int getProcessRank();
};