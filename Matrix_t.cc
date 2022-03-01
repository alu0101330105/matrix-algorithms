#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <chrono>
#include <fstream>

// Clase matriz para números enteros
class Matrix_t {
  protected:
    std::vector<std::vector<int>> _matrix = {{}};
  public:
    Matrix_t(int n = 0, int m = 0) {
      _matrix.resize(n);
      for (auto& it : _matrix) {
        it.resize(m);
      };
    };

    ~Matrix_t() {};

    int& at(int i, int j) {
      return _matrix[i][j];
    };

    int row_size() const {
      return _matrix.size();
    }

    int col_size() const {
      return _matrix[0].size();
    }


    void fill() {
      // srand(time(NULL));
      srand(1);
      for (auto& row : _matrix) {
        for (auto& cell : row) {
          cell = rand() % 200 - 100;
        }
      }
    }

    void print() const {
      for (auto& row : _matrix) {
        for (auto& cell : row) {
          std::cout << cell << "\t";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }
};

class Algorithm {
  public: 
    virtual std::chrono::nanoseconds Multiply(Matrix_t, Matrix_t) = 0;
};



class Byrows : public Algorithm  {
  std::chrono::nanoseconds Multiply(Matrix_t A, Matrix_t B) {
    Matrix_t result(A.row_size(), B.col_size());
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int row = 0; row < result.row_size(); row++) {
      for (int col = 0; col < result.col_size(); col++){
        result.at(row, col) = 0;
        for (int k = 0; k < B.col_size(); k++)
          result.at(row, col) += A.at(row, k) * B.at(k, row);
      }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Algorithmo Byrows tardó: " << elapsed.count() << " ns\n";
    // result.print();
    return elapsed;
  }
};

 

class Bycols : public Algorithm  {
  std::chrono::nanoseconds Multiply(Matrix_t A, Matrix_t B) {
    Matrix_t result(A.row_size(), B.col_size());
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int col = 0; col < result.col_size(); col++) {
      for (int row = 0; row < result.row_size(); row++){
        result.at(row, col) = 0;
        for (int k = 0; k < B.col_size(); k++)
          result.at(row, col) += A.at(row, k) * B.at(k, row);
      }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Algorithmo Bycols tardó: " << elapsed.count() << " ns\n";
    // result.print();
    return elapsed;
  }

};


class Method {
  private:
    Algorithm *_strategy;
  public:
    Method(Algorithm *strategy) {
      _strategy = strategy;
    }
  
    std::chrono::nanoseconds Interface(Matrix_t A, Matrix_t B) {
      return _strategy -> Multiply(A, B);
      
    }
};


int main() {
  std::fstream fs;
  fs.open("output.txt", std::fstream::out);
  int rows = 10;
  int cols = 10;
  int iterations = 50;


  Matrix_t mat1(rows,cols);
  Matrix_t mat2(cols,rows);

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; i++) {
    mat1.fill();
    mat2.fill();

    Method *test, *test2;
    test = new Method(new Byrows());
    fs << test->Interface(mat1, mat2).count() << " ";
    test2 = new Method(new Bycols());
    fs << test2->Interface(mat1, mat2).count() << "\n";
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "\n\nIteraciones terminadas, el programa tardó: " << elapsed.count() << " ms\nPuede consultar todos los tiempor en el archivo \"output.txt\"\n";

  fs.close();
}