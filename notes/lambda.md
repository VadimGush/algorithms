# C++ lambdas

Lambda - compiler generated struct with overloaded `operator()`. Struct contains function itself and all captured values.

```c++
// Simple lambda with one captured value
int a = 3;
auto f = [=](){};

// Compiler will generate something like this
struct lambda_t {          // object with operator()
  void operator()() const; // function itself
  int a;                   // captured value
};
```

Lambda captures only local non-static context: 
```c++
int a = 0;

void function(int d) {
  d = 4;
  int b = 2;
  static int c = 3;

  // d and b are captured (saved into generated struct)
  auto f = [=](){};
  f(); // a = 0, d = 4, b = 2, c = 3
  
  a = 1; b = 1; c = 1; d = 1;
  f(); // a = 1, d = 4; b = 2; c = 1
}
```

You can define what you want to capture
```c++
int a = 0;
int b = 0;

auto f1 = [a, b](){}; // capture by value
auto f2 = [&a, &b](){};// capture by reference

auto f5 = [la = a * 3](){}; // expression
auto f6 = [&la = a](){};    // renamed
// everything by value and "a" by reference
auto f7 = [=, &la = a](){}; 
```

There are `mutable` specifier for the lambda which allows to change captured values:
```c++
int a = 0;
auto f = [=]() mutable { a = 3; };
```

But remember in order to make lambda work in classes, you need to capture `this`:
```c++
struct some {
  int x;
  void function() {
    // FAIL (this is unknown)
    [x]() mutable { x += 3; }; 
    [&x]() mutable { x += 3; }; 
    
    // OK
    [=]() mutable { x += 3; }; 
    [&]() mutable { x += 3; };
    [this]() mutable { x += 3; };
  }
};
```

You can use `std::function<>()` to specify type of the lambda:
```c++
std::function<int()> factory(int a, int b) {
  return [&a, &b] { return a + b; }
}
```