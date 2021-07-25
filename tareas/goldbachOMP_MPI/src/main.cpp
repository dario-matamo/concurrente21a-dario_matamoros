// Copyright 2021 Donaldo Salas-Loria, Dario Matamoros, Manfred Carvajal
#include <iostream>
#include <omp.h>
#include "GoldbachCalculator.hpp"
using namespace std;



int main(int argc, char* argv[]) {
  GoldbachCalculator* g = new GoldbachCalculator(6);
  g->calculateGoldbach(6);
  std::vector<int64_t> *c = g->getQueue();
  for (auto ir = c->crbegin(); ir != c->crend(); ++ir){
    cout<<to_string(*ir);
  }
  return 0;
}
