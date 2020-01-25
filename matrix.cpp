#include "matrix.hpp"

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

double Matrix::getDeterminant() {
  return 0;
}

std::ostream& operator<<(std::ostream &os, Matrix& mtx) {
  unsigned int i = 0;
  for (double& num : mtx.list) {
    if (i++ > 0) os << " | ";
    os << num;
    if (i == mtx.width) {
      i = 0;
      os << "\n";
    }
  }
  return os;
}
