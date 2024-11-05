#include "bstmap.h"
#include <assert.h>
#include <vector>
//#include <algorithm>
#include <iostream>

class BstMapTester {
public:
  void testAdd() {
    BstMap<int, int> test1;
    test1.add(2, 22);
    assert(test1.root->key == 2);
    assert(test1.root->val == 22);
    assert(test1.root->left == NULL);
    assert(test1.root->right == NULL);
    test1.add(0, 0);
    assert(test1.root->left->key == 0);
    assert(test1.root->left->val == 0);
    assert(test1.root->left->left == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right == NULL);
    test1.add(-1, -2);
    assert(test1.root->left->left->key == -1);
    assert(test1.root->left->left->val == -2);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right == NULL);
    test1.add(4, 44);
    assert(test1.root->right->key == 4);
    assert(test1.root->right->val == 44);
    assert(test1.root->right->left == NULL);
    assert(test1.root->right->right == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->left->key == 0);
    assert(test1.root->left->left->key == -1);
    test1.add(3, 33);
    assert(test1.root->right->left->key == 3);
    assert(test1.root->right->left->val == 33);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->key == 2);
    assert(test1.root->left->key == 0);
    assert(test1.root->left->left->key == -1);
    assert(test1.root->left->right == NULL);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->key == 4);
    assert(test1.root->right->right == NULL);
    test1.add(5, 55);
    assert(test1.root->key == 2);
    assert(test1.root->left->key == 0);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right->key == 4);
    assert(test1.root->left->left->key == -1);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->left->key == 3);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->right->right->key == 5);
    assert(test1.root->right->right->left == NULL);
    assert(test1.root->right->right->right == NULL);
    test1.add(0, 100); // update
    assert(test1.root->key == 2);
    assert(test1.root->left->key == 0);
    assert(test1.root->left->val == 100);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right->key == 4);
    assert(test1.root->left->left->key == -1);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->left->key == 3);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->right->right->key  == 5);
    assert(test1.root->right->right->left == NULL);
    assert(test1.root->right->right->right == NULL);
  }

  void testFind() {
    BstMap<int, int> test1;
    int arr[] = {10, 16, 6, 12, 20, 8, 2};
    std::vector<int> vec;
    for (int i = 0; i < 7; ++i) {
      vec.push_back(arr[i]);
    }
    for (size_t i = 0; i < vec.size(); ++i) {
      test1.add(vec[i], vec[i] * 2);
    }
    for (int i = 0; i < 7; ++i) {
      assert(test1.lookup(vec[i]) == vec[i] * 2);
    }
  }

  void testRemove() {
    BstMap<int, float> test1;
    int arr[] = {10, 16, 6, 12, 20, 8, 2};
    for (size_t i = 0; i < 7; ++i) {
      test1.add(arr[i], arr[i] * 2.2);
    }
    test1.remove(2);
    assert(test1.root->left->left == NULL);
    assert(test1.root->key == 10);
    assert(test1.root->right->key == 16);
    assert(test1.root->right->left->key == 12);
    assert(test1.root->right->left->left == NULL);
    assert(test1.root->right->left->right == NULL);
    assert(test1.root->right->right->key == 20);
    assert(test1.root->left->right->key == 8);
    assert(test1.root->left->right->left == NULL);
    assert(test1.root->left->right->right == NULL);
    test1.remove(6);
    assert(test1.root->key == 10);
    assert(test1.root->left->key == 8);
    assert(test1.root->left->left == NULL);
    assert(test1.root->left->right == NULL);
    assert(test1.root->right->key == 16);
    test1.remove(16);
    assert(test1.root->left->key == 8);
    assert(test1.root->right->key == 12);
    assert(test1.root->right->left == NULL);
    assert(test1.root->right->right->key == 20);
    assert(test1.root->right->right->left == NULL);
    assert(test1.root->right->right->right == NULL);
    test1.remove(12);
    assert(test1.root->left->key == 8);
    assert(test1.root->right->key == 20);
    assert(test1.root->right->left == NULL);
    assert(test1.root->right->right == NULL);
    test1.remove(8);
    assert(test1.root->key == 10);
    assert(test1.root->left == NULL);
    assert(test1.root->right->key == 20);
    test1.remove(10);
    assert(test1.root->key == 20);
    assert(test1.root->left == NULL);
    assert(test1.root->right == NULL);
    test1.remove(20);
    assert(test1.root == NULL);
  }

  void testRemove2() {
    BstMap<int, int> test1;
    int arr[] = {20, 15, 22, 8, 17, 7, 10, 9, 12};
    for (size_t i = 0; i < 9; ++i) {
      test1.add(arr[i], arr[i] * 2);
    }
    test1.remove(15);
    assert(test1.root->left->key == 12);
    assert(test1.root->left->right->key == 17);
    assert(test1.root->left->left->key == 8);
    assert(test1.root->left->left->right->key == 10);
    assert(test1.root->left->left->left->key == 7);
    assert(test1.root->left->right->right == NULL);
    assert(test1.root->left->left->right->right == NULL);
    assert(test1.root->left->left->right->left->key == 9);
    test1.remove(12);
    assert(test1.root->left->key == 10);
    assert(test1.root->left->right->key == 17);
    assert(test1.root->left->left->right->key == 9);
    assert(test1.root->left->left->right->left == NULL);
    assert(test1.root->left->left->right->right == NULL);
    assert(test1.root->left->left->left->key == 7);
    assert(test1.root->left->left->left->left == NULL);
    assert(test1.root->left->left->left->right == NULL);
    test1.remove(10);
    assert(test1.root->left->key == 9);
    assert(test1.root->left->right->key == 17);
    assert(test1.root->left->left->key == 8);
    assert(test1.root->left->left->left->key == 7);
    assert(test1.root->left->left->right == NULL);
    test1.remove(9);
    assert(test1.root->left->key == 8);
    assert(test1.root->left->val == 16);
    assert(test1.root->left->left->key == 7);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->left->left->left ==NULL);
    assert(test1.root->left->right->key == 17);
    //test1.add(16, 32);
    //test1.remove(20);
    test1.remove(20);
    assert(test1.root->key == 17);
    assert(test1.root->left->key == 8);
    assert(test1.root->left->right == NULL);
    assert(test1.root->left->left->key == 7);
    assert(test1.root->left->left->left == NULL);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->right->key == 22);
  }

  void testRemove3() {
    BstMap<double, double> test1;
    test1.add(6, 12);
    test1.add(1, 2);
    test1.add(7, 14);
    test1.add(0, 0);
    test1.add(3, 6);
    test1.add(-1, -2);
    test1.add(0.5, 1);
    test1.add(2, 4);
    test1.add(4, 8);
    test1.remove(1);
    assert(test1.root->left->key == 0.5);
    assert(test1.root->left->left->key == 0);
    assert(test1.root->left->left->right == NULL);
    assert(test1.root->left->right->key == 3);
    test1.remove(6);
    assert(test1.root->key == 4);
    assert(test1.root->left->key == 0.5);
    assert(test1.root->left->right->key == 3);
    assert(test1.root->left->right->right == NULL);
    assert(test1.root->left->right->left->key == 2);
    test1.remove(4);
    assert(test1.root->key == 3);
    assert(test1.root->left->key == 0.5);
    assert(test1.root->left->right->key == 2);
  }

  void testCopyConstructor() {
    BstMap<int, int> test1;
    BstMap<int, int> test2(test1);
    //std::cout << test2.root << "\n";
    assert(test2.root == NULL);
    test1.add(1, 2);
    test1.add(0, 0);
    test1.add(3, 6);
    BstMap<int, int> test3(test1);
    assert(test3.root->key == 1);
    assert(test3.root->left->key == 0);
    assert(test3.root->right->key == 3);
    assert(test3.root->left->left == NULL);
    assert(test3.root->left->right == NULL);
    assert(test3.root->right->left == NULL);
    assert(test3.root->right->right == NULL);
  }

  void testAssignmentOperator() {
    BstMap<int, int> test1;
    BstMap<int, int> test2 = test1;
    assert(test2.root == NULL);
    test2.add(1, 2);
    test2.add(3, 6);
    test2.add(0, 0);
    test2 = test1;
    assert(test2.root == NULL);
    test2.add(1, 2);
    test2.add(3, 6);
    test2.add(0, 0);
    test1 = test2;
    assert(test1.root->key == 1);
    assert(test1.root->left->key == 0);
    assert(test1.root->right->key == 3);
  }
};


int main(void) {
  BstMapTester test;
  test.testAdd();
  test.testFind();
  test.testRemove();
  test.testRemove2();
  test.testRemove3();
  test.testCopyConstructor();
  test.testAssignmentOperator();
}
