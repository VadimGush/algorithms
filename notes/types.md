# Types

```c++
int b = 0;

// decltype() gives declared type of some variable
decltype(b) a = 0;

// declval() gives you reference of some type
// even if default constructor is deleted
decltype(declval<Struct>().foo());

// when you're referencing some type
// you need to specify "typename" keyword
// otherwise compiler will treat it as a variable
typename struct::type a; // if type = int, then "int a" is defined
```

## Tuples

```c++
auto tuple = make_tuple(3, 1.14, "Hello world");
get<0>(tuple); // -> 3
get<1>(tuple); // -> 1.14
get<int>(tuple); // -> 3


tuple<int, int> foo();
int a, b;
tie(a, b) = foo();
// tie will take references to those variables
// and update them because of operator=()

// OR
tuple<int, int> foo();
auto [a, b] = foo();
auto&& [a, b] = foo();

int a[2] = {1, 2};
auto [a, b] = a;

struct {int x, int y} b = {3, 1};
auto [x, y] = b;

// MAGIC TIME!
void swap(int& a, int& b, int& c, int& d) {
  tie(b, c, d, a) = make_tuple(a, b, c, d);
}

bool compare(const Point& p) {
  return tie(a, b, c) < tie(p.x, p.y, p.z);
}

int add(int x, int y) {}
std::apply(add, make_tuple(0, 1));
```

# Type deduction

## Variables

Basic type deduction for templates:
```c++
// cv-qualifiers and reference are omitted
template <typename T>
void f1(T argument);

// refs and qualifiers will not be omitted
template <typename T>
void f2(T& argument);

const int i = 3;
int& a = i;
f1(i); // -> int
f1(i); // -> int

f2(i); // -> const int&
f2(i); // -> int&
```

You can use the same rules for template type deduction for variable by using `auto` keyword:
```c++
// Same as type deduction for templates
const int a = 0;
const int& r = a;
auto b = a; // -> int
auto c = r; // -> int

auto& b = a; // -> const int& 
const auto c = r; // -> const int
```

If you want to get exactly the same type you can use `decltype()`:
```c++
const int a = 0;
const int& b = a;

decltype(b) b1 = b; // -> const int&
// or if you don't want to write right part 2 times
decltype(auto) b2 = b; // -> const int&
// WARNING
decltype((a)) b3 = a; // -> const int& 
```

But what if you want to create new variable using `auto` but there is nothing to deduce type from:
```c++
const int a = 0;

auto b = 0; // -> we want type from A variable
decay_t<decltype(a)> c = 0; // -> int
```

## Functions

You can use `auto` in return type:
```c++
template <typename T>
auto function(T a) {
  return a;
}

// we can't put decltype in return type because we don't have yet arguments names
// and because of that we use special "-> T" syntax
template <typename T>
auto function(T a) -> decltype(a) {
  return a;
}

// OR
template <typenam T>
decltype(auto) function(T a) {
  return a; // T
  // BUT
  return (a); // T&
}
```
