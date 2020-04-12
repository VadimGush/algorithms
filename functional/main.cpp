#include "Optional.h"
#include <string>
#include <iostream>
#include <optional>

using namespace std;

class Person {
public:
  explicit Person(string name) : name_(move(name)) {
    cout << "Constructor with parameter" << endl;
  }

  Person(const Person& person) {
    cout << "Copy constructor" << endl;
    name_ = person.name_;
  }

  Person(Person&& person) {
    cout << "Move constructor" << endl;
    name_ = std::move(person.name_);
  }

  const string& getName() const {
    return name_;
  }

  ~Person() =default;
private:
  string name_;
};

int main() {

  Optional<Person> another("Vadim");
  another.ifPresent([](const Person& value){ cout << value.getName() << endl; });

  another.map<string>([](const Person& person){ return person.getName(); })
    .ifPresent([](const string& value){ cout << "Name is: " << value << endl;});

  Optional<Person> empty_person;
  Optional<string> empty_name = empty_person.map<string>([](auto& value){ return value.getName(); });
  if (empty_name.isEmpty()) {
    cout << "Name is not presented" << endl;
  }

  return 0;
}

