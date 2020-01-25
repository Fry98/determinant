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
  return list[x + (y * width)];
}

void Matrix::set(unsigned int x, unsigned int y, double value) {
  if (x > width - 1) throw std::exception("Invalid X coordinate");
  if (y * width > list.size()) throw std::exception("Invalid Y coordinate");
  list[x + (y * width)] = value;
}

double Matrix::getDeterminant() {
  for (unsigned int i = 0; i < width; i++) {
    double pivot = get(i, i);
    for (unsigned int j = 0; j < width; j++) {
      if (i == j) continue;
      for (unsigned int k = i + 1; k < width; k++) {
        double divider = i == 0 ? 1 : get(i - 1, i - 1);
        double a = pivot * get(j, k);
        double b = get(j, i) * get(i, k);
        set(j, k, (a - b) / divider);
      }
    }
  }

  return get(width - 1, width - 1);
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
