#ifndef HPP_BSTSET
#define HPP_BSTSET

#include <cstdlib>
#include <stdexcept>
//#include "bst.h" // inheritance is not efficient
#include "set.h"

template<typename K>
class BstSet : public Set<K> {
private:
  class Node {
  public:
    Node* left;
    Node* right;
    K key;
    Node(): left(NULL), right(NULL), key(K()) {}
    Node(Node* l, Node* r, K key_): left(l), right(r), key(key_) {}
    Node(K key_): left(NULL), right(NULL), key(key_) {}
  };


  Node* root;


public:
  BstSet(): root(NULL) {}
  BstSet(Node* root_): root(root_) {}
  BstSet(const BstSet& rhs) {
    this->root = NULL;
    this->add(rhs.root);
  }
  virtual ~BstSet() {
    // post order traversal
    deleteNode(this->root);
  }


private:
  void deleteNode(Node* root) {
    if (NULL == root) {
      return;
    }
    deleteNode(root->left);
    deleteNode(root->right);
    delete root;
  }

  void add(Node* root) {
    if (NULL == root) {
      return;
    }
    this->add(root->key);
    this->add(root->left);
    this->add(root->right);
  }

public:
  virtual BstSet& operator=(const BstSet& rhs) {
    if (this != &rhs) {
      Node* tmp = this->root;
      this->root = NULL;
      this->add(rhs.root);
      deleteNode(tmp);
    }
    return *this;
  }

  virtual void add(const K& key) {
    Node** cur = &this->root;
    while (NULL != *cur) {
      if (key == (*cur)->key) {
        return;
      } else if (key < (*cur)->key) {
        cur = &(*cur)->left;
      } else {
        cur = &(*cur)->right;
      }
    }
    // no existing, found the position
    *cur = new Node(key);
  }

  virtual bool contains(const K& key) const {
    Node* cur = this->root;
    while (NULL != cur) {
      if (key == cur->key) {
        return true;
      } else if (key < cur->key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    // key not found
    return false;
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
      to_remove = *next_smaller;
      *next_smaller = (*next_smaller)->left;
    }
    delete to_remove;
  }

  friend class BstSetTester;
};

#endif
