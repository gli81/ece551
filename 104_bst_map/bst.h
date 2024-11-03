#ifndef HPP_BST
#define HPP_BST

#include <cstdlib>
#include <stdexcept>

template<typename K>
class Bst {
private:
  class Node {
  public:
    Node* left;
    Node* right;
    K data;


    Node(): left(NULL), right(NULL), data(K()) {}
    Node(Node* l, Node* r, K data_): left(l), right(r), data(data_) {}
    Node(K data_): left(NULL), right(NULL), data(data_) {}
  };

  Node* root;
public:
  Bst(): root(NULL) {}
  Bst(Node* r): root(r) {}
  virtual ~Bst<K>() {
    // post traversal to delete Node
  }

  virtual void add(const K& data_) {
    Node** cur = &this->root;
    while (NULL != *cur) {
      if (data_ < (*cur)->data) {
        cur = &(*cur)->left;
      } else {
        cur = &(*cur)->right;
      }
    }
    *cur = new Node(data_);
  }

  virtual bool lookup(const K& data_) const {
    Node* cur = this->root;
    while (NULL != cur) {
      if (data_ == cur->data) {
        return true;
      } else if (data_ < cur->data) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    return false;
  }

  virtual void remove(const K& data_) {
    // find Node's parent
    Node** cur = &this->root;
    //Node** prev = NULL;
    while (NULL != *cur) {
      if (data_ == (*cur)->data) {
        break;
      } else if (data_ < (*cur)->data) {
        //prev = cur;
        cur = &(*cur)->left;
      } else {
        //prev = cur;
        cur = &(*cur)->right;
      }
    }
    if (NULL == *cur) {
      // not found
      throw std::invalid_argument("Element not found");
    }
    Node* to_remove = *cur;
    if (NULL == (*cur)->left) {
      *cur = (*cur)->right;
    } else if (NULL == (*cur)->right) {
      *cur = (*cur)->left;
    } else {
      // neither is NULL
      // find the largest smaller node
      Node** next_smaller = &(*cur)->left;
      while (NULL != (*next_smaller)->right) {
        next_smaller = &(*next_smaller)->right;
      }
      // swap value
      (*cur)->data = (*next_smaller)->data;
      to_remove = *next_smaller;
      *next_smaller = NULL;
    }
    delete to_remove;
  }

  friend class BstTester;
};

#endif
