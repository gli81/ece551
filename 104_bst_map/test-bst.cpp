#include "bst.h"
#include <assert.h>
#include <vector>
#include <algorithm>

class BstTester {
public:
  void testAdd() {
    Bst<int> test1;
    test1.add(2);
    assert(test1.root->data == 2);
    assert(test1.root->left == NULL);
    assert(test1.root->right == NULL);
    test1.add(0);
    assert(test1.root->left->data == 0);
    assert(test1.root->left->left == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right == NULL);
    test1.add(-1);
    assert(test1.root->left->left->data == -1);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right == NULL);
    test1.add(4);
    assert(test1.root->right->data == 4);
    assert(test1.root->right->left == NULL);
    assert(test1.root->right->right == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->left->data == 0);
    assert(test1.root->left->left->data == -1);
    test1.add(3);
    assert(test1.root->right->left->data == 3);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->data == 2);
    assert(test1.root->left->data == 0);
    assert(test1.root->left->left->data == -1);
    assert(test1.root->left->right == NULL);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->data == 4);
    assert(test1.root->right->right == NULL);
    test1.add(5);
    assert(test1.root->data == 2);
    assert(test1.root->left->data == 0);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right->data == 4);
    assert(test1.root->left->left->data == -1);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->left->data == 3);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->right->right->data == 5);
    assert(test1.root->right->right->left == NULL);
    assert(test1.root->right->right->right == NULL);
    test1.add(0);
    assert(test1.root->data == 2);
    assert(test1.root->left->data == 0);
    assert(test1.root->left->right->data == 0);
    assert(test1.root->left->right->left == NULL);
    assert(test1.root->left->right->right == NULL);
    assert(test1.root->right->data == 4);
    assert(test1.root->left->left->data == -1);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->left->data == 3);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->right->right->data == 5);
    assert(test1.root->right->right->left == NULL);
    assert(test1.root->right->right->right == NULL);
  }

  void testFind() {
    Bst<int> test1;
    int arr[] = {10, 16, 6, 12, 20, 8, 2};
    std::vector<int> vec;
    for (int i = 0; i < 7; ++i) {
      vec.push_back(arr[i]);
    }
    for (size_t i = 0; i < vec.size(); ++i) {
      test1.add(vec[i]);
    }
    for (int i = 0; i < 21; ++i) {
      if (std::find(vec.begin(), vec.end(), i) != vec.end()) {
        // found
        assert(test1.lookup(i));
      } else {
        assert(!test1.lookup(i));
      }
    }
  }

  void testRemove() {
    Bst<int> test1;
    int arr[] = {10, 16, 6, 12, 20, 8, 2};
    for (size_t i = 0; i < 7; ++i) {
      test1.add(arr[i]);
    }
    test1.remove(2);
    assert(test1.root->left->left == NULL);
    assert(test1.root->data == 10);
    assert(test1.root->right->data == 16);
    assert(test1.root->right->left->data == 12);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->right->right->data == 20);
    assert(test1.root->left->right->data == 8);
    assert(test1.root->left->right->left == NULL);
    assert(test1.root->left->right->right == NULL);
    test1.remove(6);
    assert(test1.root->data == 10);
    assert(test1.root->left->data == 8);
    assert(test1.root->left->left == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right->data == 16);
    test1.remove(16);
    assert(test1.root->left->data == 8);
    assert(test1.root->right->data == 12);
    assert(test1.root->right->left == NULL);
    assert(test1.root->right->right->data == 20);
    assert(test1.root->right->right->left == NULL);
    assert(test1.root->right->right->right == NULL);
    test1.remove(12);
    assert(test1.root->left->data == 8);
    assert(test1.root->right->data == 20);
    assert(test1.root->right->left == NULL);
    assert(test1.root->right->right == NULL);
    test1.remove(8);
    assert(test1.root->data == 10);
    assert(test1.root->left == NULL);
    assert(test1.root->right->data == 20);
    test1.remove(10);
    assert(test1.root->data == 20);
    assert(test1.root->left == NULL);
    assert(test1.root->right == NULL);
    test1.remove(20);
    assert(test1.root == NULL);
  }
};


int main(void) {
  BstTester test;
  test.testAdd();
  test.testFind();
  test.testRemove();
}
