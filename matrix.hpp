#include <vector>

class Matrix {
  private:
    std::vector<int> list;
    int width;
  public:
    void add(int number);
    void setWidth(int width);
    bool isSquare();
    int get(int x, int y);
};
