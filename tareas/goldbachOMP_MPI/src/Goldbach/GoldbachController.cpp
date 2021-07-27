#include "GoldbachController.hpp"
int GoldbachController::calculateLastIndex(int rank, int arraySize,
int processCount) {
  const int lastIndex =
  calculateFirstIndex(rank + 1, arraySize, processCount);
  return lastIndex;
}
int GoldbachController::calculateFirstIndex(int rank, int arraySize
, int processCount) {
  int startIndex = rank * (arraySize / processCount)
  +std::min(rank,processCount % arraySize);
  return startIndex;
}
GoldbachController::GoldbachController(int processRank, int processCount) {
  this->processRank = processRank;
  this->processCount = processCount;
}
int GoldbachController::getProcessCount(){
    return this->processCount;
}
int GoldbachController::getProcessRank(){
    return this->processRank;
}