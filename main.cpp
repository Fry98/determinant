#include <iostream>
#include <string>
#include <fstream>
#include <future>
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

double matrix_from_std() {
  Matrix mtx;
  std::string line;
  int line_length = -1;

  while (std::getline(std::cin, line)) parse_line(mtx, line, line_length);
  mtx.setWidth(line_length);
  if (!mtx.isSquare()) throw std::exception("Invalid matrix size");
  return mtx.getDeterminant();
}

double matrix_from_file(const std::string name) {
  std::ifstream file;
  std::string line;
  Matrix mtx;
  int line_length = -1;

  file.open(name);
  if (!file.is_open()) throw std::exception("File not found");
  while (std::getline(file, line)) parse_line(mtx, line, line_length);
  mtx.setWidth(line_length);
  file.close();
  if (!mtx.isSquare()) throw std::exception("Invalid matrix size");
  return mtx.getDeterminant();
}

void print_help() {
  std::cout <<
    "(--input | -i) <filename1>;<filename2>;...  <- List of input files containing matrices (If none are specified, the program will be expecting input from std)\n"
    "(--output | -o) <filename>  <- Filename of the file where you want the results to be saved (If not provided, the results will be written into std)\n"
    "--result-only | -ro  <- Outputs only the results without prefixing the index"
    "--single-thread | -st  <- Forces program to run on a single thread\n"
    "--perf-comp | -pc  <- Runs the computations in both multi-threaded and single-threaded mode and compares the preformance\n"
    "--help  <- Prints the list of valid commands\n";
}

int main(unsigned int argc, char* argv[]) {
  bool res_only = false;
  unsigned char thread_mode = 0;
  char* inp = nullptr;
  char* out = nullptr;

  try {
    for (unsigned int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "--result-only") == 0 || strcmp(argv[i], "-ro") == 0) {
        res_only = true;
      } else if (strcmp(argv[i], "--single-thread") == 0 || strcmp(argv[i], "-st") == 0) {
        if (thread_mode == 0) thread_mode = 1;
      } else if (strcmp(argv[i], "--perf-comp") == 0 || strcmp(argv[i], "-pc") == 0) {
        thread_mode = 2;
      } else if (strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-i") == 0) {
        if (i + 1 >= argc) throw std::exception("Input flag requires path argument");
        inp = argv[++i];
      } else if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0) {
        if (i + 1 >= argc) throw std::exception("Output flag requires path argument");
        out = argv[++i];
      } else if (strcmp(argv[i], "--help") == 0) {
        print_help();
        return 0;
      } else {
        throw std::runtime_error("Invalid argument: \"" + std::string(argv[i]) + "\"");
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\nHere is the list of valid commands:\n";
    print_help();
    return 0;
  }

  try {
    std::ostream* outs = &std::cout;
    std::ostream* errs = &std::cerr;
    std::ofstream outfile;
    if (out != nullptr) {
      outfile.open(out, std::ios_base::trunc);
      if (!outfile.is_open()) throw std::exception("Invalid filename");
      outs = &outfile;
      errs = &outfile;
    }
    if (inp == nullptr) {
      double det = matrix_from_std();
      if (!res_only) *outs << "(1) ";
      *outs << det;
    } else {
      std::string filename = "";
      std::vector<std::future<double>> futures;
      for (unsigned int i = 0; inp[i] != 0; i++) {
        if (inp[i] != 59) {
          filename += inp[i];
        } else {
          if (filename.size() == 0) throw std::exception("Invalid filename");
          futures.push_back(std::async(&matrix_from_file, filename));
          filename = "";
        }
      }
      if (filename.size() != 0) {
        futures.push_back(std::async(&matrix_from_file, filename));
      }
      for (unsigned int i = 0; i < futures.size(); i++) {
        if (!res_only) *outs << "(" << i + 1 << ") ";
        try {
          *outs << futures[i].get() << "\n";
        } catch (const std::exception& e) {
          *errs << e.what() << "\n";
        }
      }
    }
    if (out != nullptr) outfile.close();
  } catch(const std::exception& e) {
    std::cerr << e.what() << "\n";
  }
}
