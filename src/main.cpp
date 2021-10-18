#include <iostream>
#include "structure/ArrayDeque.h"
#include "structure/Vector.h"
#include "structure/SkiplistSet.h"
using namespace std;

struct Value {
};

int main(){

  gush::Vector<unique_ptr<int>> vector;
  vector.push_back(make_unique<int>(3));
  auto value = vector.remove(0);
  for (const auto& value : vector) {
    cout << value << endl;
  }
  return 0;
}