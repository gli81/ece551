#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  // build pq
  priority_queue_t pq;
  for (size_t i = 0; i < 257; ++i) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  if (pq.size() == 0) {
    return NULL;
  }
  while (pq.size() > 1) {
    Node* first = pq.top();
    pq.pop();
    Node* second = pq.top();
    pq.pop();
    pq.push(new Node(first, second));
  }
  // left with pq.size() == 1
  return pq.top();
} 
