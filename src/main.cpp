#include <iostream>
#include "structure/vector.h"
#include "structure/list.h"
using namespace std;

int main(){

  gush::list<int> list;

  gush::vector<int> v1{3, 2, 3};
  v1.push_back(7);
  v1.push_back(0);
  v1.push_back(10);
  for (const auto& value : v1) {
    cout << value << endl;
  }

  return 0;
}