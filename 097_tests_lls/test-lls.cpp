#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(1);
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->data == 1);
    assert(il.getSize() == 1);
    il.addFront(2);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 1);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.head->next->prev->data == 2);
    assert(il.getSize() == 2);
    il.addBack(3);
    // 2, 1, 3
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 1);
    assert(il.tail->prev->data == 1);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->next->data == 3);
    assert(il.getSize() == 3);
    // add to a new list
    IntList il2;
    il2.addBack(10);
    assert(il2.head->data == 10);
    assert(il2.head->prev == NULL);
    assert(il2.head->next == NULL);
    assert(il2.tail->data == 10);
    assert(il2.tail->next == NULL);
    assert(il2.tail->prev == NULL);
  }

  // many more tester methods
  void testRuleOfThree() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    {
      IntList il_copy(il);
      IntList il2;
      il2 = il;
      assert(il_copy.head== NULL);
      assert(il2.head == NULL);
      assert(il_copy.tail== NULL);
      assert(il2.tail == NULL);
    }
    il.addFront(3);
    il.addFront(2);
    il.addFront(1);
    // 1, 2, 3
    {
      IntList il_copy(il);
      IntList il2;
      il2 = il;
      assert(il_copy.head->data == 1);
      assert(il_copy.head->prev == NULL);
      assert(il_copy.head->next->data == 2);
      assert(il_copy.head->next->prev == il_copy.head);
      assert(il_copy.tail->data == 3);
      assert(il_copy.tail->next == NULL);
      assert(il_copy.tail->prev->data == 2);
      assert(il_copy.tail->prev->next == il_copy.tail);
      assert(il2.head->data == 1);
      assert(il2.head->prev == NULL);
      assert(il2.head->next->data == 2);
      assert(il2.head->next->prev == il2.head);
      assert(il2.tail->data == 3);
      assert(il2.tail->next == NULL);
      assert(il2.tail->prev->data == 2);
      assert(il2.tail->prev->next == il2.tail);
    }
    {
      // test move il2 to a new empty list
      IntList il2;
      il2 = il;
      IntList il3;
      il2 = il3;
      assert(il2.head == NULL);
      assert(il2.tail == NULL);
      assert(il2.getSize() == 0);
    }
  }

  void testRemove() {
    IntList il;
    assert(il.remove(1) == false);
    assert(il.getSize() == 0);
    il.addFront(3);
    il.addFront(2);
    il.addFront(1);
    // 1, 2, 3
    assert(il.remove(1) == true);
    assert(il.remove(1) == false);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->data == 3);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
    assert(il.remove(3) == true);
    assert(il.remove(3) == false);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->data == 2);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);
    assert(il.remove(2) == true);
    assert(il.remove(2) == false);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    il.addFront(3);
    il.addFront(2);
    il.addFront(1);
    assert(il.remove(5) == false);
    assert(il.remove(2) == true);
    assert(il.remove(2) == false);
    assert(il.head->data == 1);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 2);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 1);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testRuleOfThree();
  t.testRemove();
  return EXIT_SUCCESS;
}
