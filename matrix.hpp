#include <vector>

class Matrix {
  private:
    std::vector<double> list;
    unsigned int width;
  public:
    void add(double number);
    void setWidth(unsigned int width);
    bool isSquare();
    double get(unsigned int x, unsigned int y);
};
