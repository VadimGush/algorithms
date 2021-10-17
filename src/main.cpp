#include <iostream>
#include "structure/ArrayQueue.h"
using namespace std;

int main(){

  gush::ArrayQueue<int> data;
  for (const auto& value : data) {
    cout << value << " ";
  }
  cout << endl;
  return 0;
}