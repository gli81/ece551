#include "IntMatrix.h"

IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c): numRows(r), numColumns(c), rows(new IntArray*[r]()) {
  for (int i = 0; i < r; ++i) {
    this->rows[i] = new IntArray(c);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs)  {
  IntArray** tmp = new IntArray*[rhs.numRows]();
  for (int i = 0; i < rhs.numRows; ++i) {
    tmp[i] = new IntArray(*rhs.rows[i]);
    //for (int j = 0; j < rhs.numColumns; ++j) {
    //  tmp[i][j] = rhs.rows[i][j];
    //}
  }
  this->rows = tmp;
  tmp = NULL;
  this->numRows = rhs.numRows;
  this->numColumns = rhs.numColumns;
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < this->numRows; ++i) {
    delete this->rows[i];
  }
  delete[] this->rows;
  this->rows = NULL;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray** tmp = new IntArray*[rhs.numRows];
    for (int i = 0; i < rhs.numRows; ++i) {
      tmp[i] = new IntArray(*rhs.rows[i]);
      //for (int j = 0; i < rhs.numColumns; ++j) {
      //  tmp[i][j] = rhs.rows[i][j];
      //}
    }
    this->rows = tmp;
    tmp = NULL;
    this->numRows = rhs.numRows;
    this->numColumns = rhs.numColumns;
  }
  return *this;
}

int IntMatrix::getRows() const {
  return this->numRows;
}

int IntMatrix::getColumns() const {
  return this->numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  return *this->rows[index];
}

IntArray & IntMatrix::operator[](int index){
  return *this->rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this->numRows != rhs.numRows) {
    return false;
  }
  for (int i = 0; i < this->numRows; ++i) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numRows == rhs.numRows && this->numColumns == rhs.numColumns);
  IntMatrix* ans = new IntMatrix(*this);
  for (int i = 0; i < ans->numRows; ++i) {
    for (int j = 0; j < ans->numColumns; ++j) {
      (*ans)[i][j] += rhs[i][j];
    }
  }
  return *ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[";
  for (int i = 0; i < rhs.getRows(); ++i) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << "]";
  return s;
}
