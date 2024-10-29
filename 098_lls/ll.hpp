#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

class item_not_exist: public std::exception {
public:
  virtual const char* what() throw () {
    return "Item Does Not Exist";
  }
};

template<typename T>
class LinkedList{
private:
  class Node {
    public:
      T data;
      Node* next;
      Node* prev;
      Node(): data(T()), next(NULL), prev(NULL) {}
      Node(const T& data_, Node* next_, Node* prev_): data(data_), next(next_), prev(prev_) {}
  };
  Node* head;
  Node* tail;
  int size;
public:
  LinkedList(): head(NULL), tail(NULL), size(0) {}
  
  LinkedList(const LinkedList& rhs) {
    Node* cur = rhs.head;
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
    while (cur != NULL) {
      this->addBack(cur->data);
      cur = cur->next;
    }
  }
  
  ~LinkedList() {
    Node* cur = this->head;
    Node* temp;
    while (cur != NULL) {
      temp = cur;
      cur = cur->next;
      delete temp;
    }
  }


  LinkedList<T>& operator=(const LinkedList& rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);
      Node* old_head = this->head;
      Node* old_tail = this->tail;
      this->head = temp.head;
      this->tail = temp.tail;
      this->size = temp.size;
      temp.head = old_head; // go to destructor, byebye
      temp.tail = old_tail;
    }
    return *this;
  }

  void addFront(const T& item) {
    this->head = new Node(item, this->head, NULL);
    if (this->tail == NULL) {
      // only node
      this->tail = this->head;
    } else {
      this->head->next->prev = this->head;
    }
    ++size;
  }

  void addBack(const T& item) {
    this->tail = new Node(item, NULL, this->tail);
    if (this->head == NULL) {
      this->head = this->tail;
    } else {
      this->tail->prev->next = this->tail;
    }
    ++size;
  }

  bool remove(const T& item) {
    Node** cur = &head;
    while (*cur != NULL) {
      if ((*cur)->data == item) {
        // remove (*cur)->next
        Node* temp = *cur;
        *cur = (*cur)->next;
        if (*cur != NULL) {
          (*cur)->prev = temp->prev;
        } else {
          this->tail = temp->prev;
        }
        delete temp;
        --this->size;
        return true;
      }
      cur = &(*cur)->next;
    }
    return false;
  }

  T& operator[](int index) {
    if (index >= this->size) {
      throw item_not_exist();
    }
    Node* ans = head;
    for (int i = 0; i < index; ++i) {
      ans = ans->next;
    }
    return ans->data;
  }

   T& operator[](int index) const {
    if (index >= this->size) {
      throw item_not_exist();
    }
    Node* ans = head;
    for (int i = 0; i < index; ++i) {
      ans = ans->next;
    }
    return ans->data;
  }

  int find(const T& item) const {
    int ans = 0;
    Node* cur = this->head;
    while (cur != NULL) {
      if (cur->data == item) return ans;
      cur = cur->next;
      ++ans;
    }
    return -1;
  }

  int getSize() const {
    return this->size;
  }

  friend class Tester;
};

#endif
