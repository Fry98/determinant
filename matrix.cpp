#include "matrix.hpp"
#include <stdexcept>

void Matrix::add(int number) {
  list.push_back(number);
}

void Matrix::setWidth(int width) {
  this->width = width;
}

bool Matrix::isSquare() {
  return width == list.size() / width;
}

int Matrix::get(int x, int y) {
  if (x > width - 1) throw std::runtime_error("Invalid X coordinate");
  if (y * width > list.size()) throw std::runtime_error("Invalid Y coordinate");
  return list[x + (y*width)];
}
