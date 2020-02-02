#include <vector>
#include <iostream>

class Matrix {
  private:
    friend std::ostream& operator<<(std::ostream &os, Matrix& mtx);
    std::vector<double> list;
    unsigned int width;
  public:
    void add(double number);
    void set(unsigned int x, unsigned int y, double value);
    void setWidth(unsigned int width);
    bool isSquare();
    double get(unsigned int x, unsigned int y);
    long double getDeterminant();
};
