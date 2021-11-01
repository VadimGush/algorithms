#include "Environment.h"

using namespace std;

optional<string> Environment::get(const string& name) {
  auto* result = getenv(name.c_str());
  if (result == nullptr) { return {}; }
  return result;
}

void Environment::set(const string& name, const string& value) {
  setenv(name.c_str(), value.c_str(), true);
}

void Environment::remove(const string& name) {
  unsetenv(name.c_str());
}
