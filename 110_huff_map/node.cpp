#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    // leaf node
    assert(this->left == NULL);
    assert(this->right == NULL);
    // update map
    theMap[sym] = b;
    return;
  }
  // internal node
  assert(this->left != NULL);
  this->left->buildMap(b.plusZero(), theMap);
  assert(this->right != NULL);
  this->right->buildMap(b.plusOne(), theMap);
}

