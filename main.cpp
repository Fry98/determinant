#include <iostream>
#include "matrix.hpp"

int main() {
  Matrix mtx;
  mtx.add(5);
  mtx.add(7);
  mtx.add(3);
  mtx.add(12);
  mtx.setWidth(2);
  std::cout << mtx.isSquare() << "\n";
  return 0;
}