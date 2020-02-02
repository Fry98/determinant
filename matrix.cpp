#include "matrix.hpp"

void Matrix::add(double number) {
  list.push_back(number);
}

void Matrix::setWidth(unsigned int width) {
  if (width < 1 || list.size() % width != 0) throw std::runtime_error("Invalid matrix width");
  this->width = width;
}

bool Matrix::isSquare() {
  return width == list.size() / width;
}

double Matrix::get(unsigned int x, unsigned int y) {
  if (x > width - 1) throw std::runtime_error("Invalid X coordinate");
  if (y * width > list.size()) throw std::runtime_error("Invalid Y coordinate");
  return list[x + (y * width)];
}

void Matrix::set(unsigned int x, unsigned int y, double value) {
  if (x > width - 1) throw std::runtime_error("Invalid X coordinate");
  if (y * width > list.size()) throw std::runtime_error("Invalid Y coordinate");
  list[x + (y * width)] = value;
}

long double Matrix::getDeterminant() {
  for (unsigned int i = 0; i < width; i++) {
    if (get(i, i) == 0) throw std::runtime_error("Division by zero");
    for (unsigned int j = i + 1; j < width; j++) {
      double ratio = get(j, i) / get(i, i);
      for (unsigned int k = 0; k < width; k++) {
        double res = get(j, k) - ratio * get(i, k);
        set(j, k, res);
      }
    }
  }

  long double det = 1.0;
  for (unsigned int i = 0; i < width; i++) {
    det *= get(i, i);
  }

  return det;
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
