#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
private:
  int numRows;
  int numColumns;
  std::vector<T>** rows;
public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix& rhs);
  ~Matrix();
  Matrix& operator=(const Matrix& rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T>& operator[](int index) const;
  std::vector<T>& operator[](int index);
  bool operator==(const Matrix& rhs) const;
  Matrix operator+(const Matrix& rhs) const;
};


template<typename T>
Matrix<T>::Matrix(): numRows(0), numColumns(0), rows(NULL) {}

template<typename T>
Matrix<T>::Matrix(int r, int c): numRows(r), numColumns(c), rows(new std::vector<T>*[r]()) {
  for (int i = 0; i < r; ++i) {
    this->rows[i] = new std::vector<T>(c);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs)  {
  std::vector<T>** tmp = new std::vector<T>*[rhs.numRows]();
  for (int i = 0; i < rhs.numRows; ++i) {
    tmp[i] = new std::vector<T>(*rhs.rows[i]); // vector(const vector& other);
  }
  this->rows = tmp;
  tmp = NULL;
  this->numRows = rhs.numRows;
  this->numColumns = rhs.numColumns;
}

template<typename T>
Matrix<T>::~Matrix() {
  for (int i = 0; i < this->numRows; ++i) {
    delete this->rows[i];
  }
  delete[] this->rows;
  this->rows = NULL;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
  if (this != &rhs) {
    std::vector<T>** tmp = new std::vector<T>*[rhs.numRows];
    for (int i = 0; i < rhs.numRows; ++i) {
      tmp[i] = new std::vector<T>(*rhs.rows[i]);
    }
    for (int i = 0; i < this->numRows; ++i) {
      delete this->rows[i];
    }
    delete[] this->rows;
    this->rows = tmp;
    tmp = NULL;
    this->numRows = rhs.numRows;
    this->numColumns = rhs.numColumns;
  }
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return this->numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return this->numColumns;
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](int index) const {
  assert(index < this->numRows && index >= 0);
  return *this->rows[index];
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](int index){
  assert(index < this->numRows && index >= 0);
  return *this->rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (this->numRows != rhs.numRows || this->numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < this->numRows; ++i) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const {
  assert(this->numRows == rhs.numRows && this->numColumns == rhs.numColumns);
  Matrix<T> ans = Matrix(*this);
  for (int i = 0; i < ans.numRows; ++i) {
    for (int j = 0; j < ans.numColumns; ++j) {
      ans[i][j] += rhs[i][j];
    }
  }
  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T>& rhs) {
  s << "[";
  for (int i = 0; i < rhs.getRows(); ++i) {
    s << "{";
    for (int j = 0; j < rhs.getColumns(); ++j) {
      if (j != 0) {
        s << ", ";
      }
      s << rhs[i][j];
    }
    s << "}";
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  return s << "]";
}

#endif
