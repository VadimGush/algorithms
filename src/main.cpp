#include <iostream>
#include "structure/Vector.h"
using namespace std;

struct Value {
};

int main(){

  gush::Vector<unique_ptr<int>> vector;
  vector.push_back(make_unique<int>(3));
  for (const auto& value : vector) {
    cout << value << endl;
  }
  return 0;
}