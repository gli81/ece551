#ifndef HPP_BSTMAP
#define HPP_BSTMAP

#include <cstdlib>
#include <stdexcept>
//#include "bst.h" // inheritance is not efficient
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
private:
  class Node {
  public:
    Node* left;
    Node* right;
    K key;
    V val;
    Node(): left(NULL), right(NULL), key(K()), val(V()) {}
    Node(Node* l, Node* r, K key_, V val_): left(l), right(r), key(key_), val(val_) {}
    Node(K key_, V val_): left(NULL), right(NULL), key(key_), val(val_) {}
  };


  Node* root;


public:
  BstMap(): root(NULL) {}
  BstMap(Node* root_): root(root_) {}
  virtual ~BstMap<K, V>() {
    
  }


  virtual void add(const K& key, const V& value) {
    Node** cur = &this->root;
    while (NULL != *cur) {
      if (key == (*cur)->key) {
        (*cur)->val = value;
        return;
      } else if (key < (*cur)->key) {
        cur = &(*cur)->left;
      } else {
        cur = &(*cur)->right;
      }
    }
    // no existing, found the position
    *cur = new Node(key, value);
  }

  virtual const V& lookup(const K& key) const throw (std::invalid_argument) {
    Node* cur = this->root;
    while (NULL != cur) {
      if (key == cur->key) {
        return cur->val;
      } else if (key < cur->key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    // key not found
    throw std::invalid_argument("Element not found");
  }

  virtual void remove(const K& key) {
    Node** cur = &this->root;
    while (NULL != *cur) {
      if (key == (*cur)->key) {
        break;
      } else if (key < (*cur)->key) {
        cur = &(*cur)->left;
      } else {
        cur = &(*cur)->right;
      }
    }
    if (NULL == *cur) {
      throw std::invalid_argument("Element not found");
    }
    Node* to_remove = *cur;
    if (NULL == (*cur)->left) {
      *cur = (*cur)->right;
    } else if (NULL == (*cur)->right) {
      *cur = (*cur)->left;
    } else {
      Node** next_smaller = &(*cur)->left;
      while (NULL != (*next_smaller)->right) {
        next_smaller = &(*next_smaller)->right;
      }
      (*cur)->key = (*next_smaller)->key;
      (*cur)->val = (*next_smaller)->val;
      to_remove = *next_smaller;
      *next_smaller = NULL;
    }
    delete to_remove;
  }

  friend class BstMapTester;
};

#endif
