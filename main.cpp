#include <iostream>
#include <string>
#include <fstream>
#include "matrix.hpp"

void parse_line(Matrix& mtx, const std::string& line, int& line_length) {
  int current_length = 0;
  std::string block = "";

  for (const char& ch : line) {
    if (ch == 46 || (ch > 47 && ch < 58)) {
      block += ch;
    } else if (block != "") {
      mtx.add(std::stod(block));
      block = "";
      current_length++;
    }
  }
  if (block != "") {
    mtx.add(std::stod(block));
    block = "";
    current_length++;
  }
  if (line_length == -1) {
    line_length = current_length;
  } else if (line_length != current_length && current_length != 0) {
    throw std::exception("Invalid matrix size");
  }
}

void fillFromStd(Matrix& mtx) {
  std::string line;
  int line_length = -1;

  while (std::getline(std::cin, line)) parse_line(mtx, line, line_length);
  mtx.setWidth(line_length);
}

void fillFromFile(Matrix& mtx, const char* name) {
  std::ifstream file;
  std::string line;
  int line_length = -1;

  file.open(name);
  if (!file.is_open()) throw std::exception("File not found");
  while (std::getline(file, line)) parse_line(mtx, line, line_length);
  mtx.setWidth(line_length);
  file.close();
}

int main(int argc, char* argv[]) {
  try {
    Matrix mtx;
    if (argc < 2) {
      fillFromStd(mtx);
    } else {
      fillFromFile(mtx, argv[1]);
    }

    if (!mtx.isSquare()) throw std::exception("Invalid matrix size");
    std::cout << "Matrix:\n" << mtx << "\nDeterminant:\n" << mtx.getDeterminant() << "\n";
  } catch(const std::exception& e) {
    std::cerr << e.what() << "\n";
  }
}
