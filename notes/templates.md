# C++ Templates

Note: you can't overload from std namespace, but you can specialize

## Class templates

Templates for structures
```c++
template <class T, class P = int> struct A {} // P has default type
template <class T, int A> struct A {} // integral, floating-point, enum types also work
```

Specialization for structures
```c++
template <> struct A<int> {} // specialization for only "int" type
template <class T> struct A<vector<T>> {} // specialization for everything that looks like "vector<T>"
```

Partial specialization (doesn't work for functions)
```c++
template <class T> struct A <T*> {} // specialization for all pointer types
```

## Hints

You can make a hint for the compiler when it's trying to deduce type from template constructor:
```c++
template <typename T>
class Vector {
  template <typename Iter>
  Vector(Iter b, Iter e) -> Vector<Iter::value_type> {}
};

// Now instead of this
collection<int> c{};
Vector<int>(c.begin(), c.end());
// you can write just
Vector(c.begin(), c.end());
```

## Function templates

Templates for functions
```c++
template <class T> void fn(T p);
```

Specialization for functions
```c++
template <> void fn<int>(int p);
template <> void fn(int p); // let compiler guess the type
```

Restrict certain types through specialization
```c++
template <> void function<int>() = delete; // delete function for type int
```

## Template as template parameter

```c++
template <template <typename> typename S, typename E>
struct Stack {};
Stack<Vector, int> s;
```

With power of C++ you can write the most unreadable code possible:
```c++
template <template <template <typename> typename, typename> typename Stack, template <typename> typename S, typename E>
struct StackMachine {};
StackMachine<Stack, Vector, int> a;
```

## Pointer as template parameter
If pointer is known on compile time, you can pass it as a template parameter:
```c++
template <void (*callback)()>
struct Callback {
  void use() { callback(); }
};
Callback<&foo> c;
c.use();
```

## CRTP
**CRTP** - curiously recurring template parameter

```c++
template <typename T> class Base {};
class Derived : public Base <derived> {};
```

This trick allows you to define interfaces for classes (or default implementation of certain methods)
on compile time.

```c++
// EBCO (empty base class optimisation) will be applied
// basically if class is empty, then overhead of deriving from that class will be zero
template <typename T> struct Base {
  T copy() {
    // copy method for every type T without any need
    // to implement in every class
  }
  void interface() {
    static_cast<T*>(this)->implementation();
  }
};

struct Derived : Base<Derived> {
  void implementation() { }
};

template <typename T>
void use(Base<T>& a) {
  a.interface();
}

Derived d;
use(d);
```

## Tricky situations

#### 2 phase name resolution
```c++
template <class T> void foo(T) { cout << "T"; }
struct S;
template <class T> void foo_bar(T t, S s) {
  foo(s); // resolved on declaration (it doesn't depend on any template param) [first phase]
  foo(t); // resolved on instantiation (it depends on yet unknown T) [second phase]
}
foo(S) { cout << "S"; }
int bar(S x) {
  foo_bar(x, x); // result: TS
}
```

```c++
template <class T> class Base { void exit() {}; }
template <class T> class Child : Base<T> {
  void foo() {
    exit(); // ERROR! we can't resolve that name on the first phase (it doesn't depend on anything)
    // FIX
    this->exit();
    Base::exit();
  }
}
```

#### Ambiguous names
```c++
struct S { struct subtype {} }
template <class T> int foo {
  S::subtype* a; // ERROR! for compiler looks like multiplication (S::member * a);
  // FIX
  typename S::subtype* a; // hey, compiler! look, it's a fucking type, not a member of a struct
}

template <class T> struct S {
   template <class U> foo() {} }
S<T> s;
s.foo<T>(); // ERROR! s.foo looks like member of type S (dammit!)
// FIX
s.template foo<T>();
```

#### Templates in templates
```c++
// What if we want to define a method which is inside two templates?
template <class T> struct S {
  template <class U> U foo();
}
// yep, you need to write template<T> two times
template <class T>
template <class U>
U foo() {}
```


