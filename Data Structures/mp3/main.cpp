#include "List.h"
#include <iostream>

using namespace std;

int main() {
  List<int> list_1;
  list_1.insertFront(9);
  list_1.insertFront(6);
  list_1.insertFront(11);
  list_1.insertFront(1);
  list_1.insertFront(4);
  list_1.insertFront(10);
  list_1.insertFront(5);
  list_1.sort();
  cout << list_1 << endl;
  return 0;
}
