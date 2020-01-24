#include "matrix.hpp"
#include <stdexcept>

void Matrix::add(double number) {
  list.push_back(number);
}

void Matrix::setWidth(unsigned int width) {
  if (width < 1 || list.size() % width != 0) throw std::exception("Invalid matrix width");
  this->width = width;
}

bool Matrix::isSquare() {
  return width == list.size() / width;
}

double Matrix::get(unsigned int x, unsigned int y) {
  if (x > width - 1) throw std::exception("Invalid X coordinate");
  if (y * width > list.size()) throw std::exception("Invalid Y coordinate");
  return list[x + (y*width)];
}
