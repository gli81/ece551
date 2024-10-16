#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray(): data(NULL), numElements(0) {}

IntArray::IntArray(int n): data(new int[n]()), numElements(n) {}

IntArray::IntArray(const IntArray & rhs): data(new int[rhs.numElements]()), numElements(rhs.numElements)  {
  for (int i = 0; i < this->numElements; ++i) {
    this->data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  if (this->data != NULL) {
    delete[] this->data;
    this->data = NULL;
  }
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int* tmp = new int[rhs.numElements]();
    for (int i = 0; i < this->numElements; ++i) {
      tmp[i] = rhs.data[i];
    }
    if (NULL != this->data) {
      delete[] this->data;
    }
    this->data = tmp;
    tmp = NULL;
    this->numElements = rhs.numElements;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < this->numElements);
  return this->data[index];
}

int & IntArray::operator[](int index) {
  assert(index < this->numElements);
  return this->data[index];
}

int IntArray::size() const {
  return this->numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this == &rhs) return true;
  if (rhs.numElements != this->numElements) {
    return false;
  }
  for (int i = 0; i < this->numElements; ++i) {
    if (this->data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); ++i) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
