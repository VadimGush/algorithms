#include "Environment.h"

using namespace std;

optional<string> Environment::get(const string& name) {
  auto* result = getenv(name.c_str());
  if (result == nullptr) { return {}; }
  return result;
}
