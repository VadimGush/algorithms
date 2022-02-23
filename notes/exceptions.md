# Exceptions

General view:
```c++
try {
  // you can throw anything
  throw 3; // int literal
  throw object{}; // any object
  throw new object{}; // ptr to object
}
// only if catch has the same EXACT type, then it will handle that exception
// (except for base classes).
// order DOES matter
catch (T e) {} // catch by value
catch (const T& e) {} // catch by const reference
catch (T* e) {} // catch by pointer
```

`noexcept` keyword:
```c++
// noexcept is special keyword which tells compiler that
// we will not throw any exception in this function (which can be false)
void foo() noexcept;

// Special operator that returns true if case provided <expr> will not throw exceptions (it's noexcept)
// or false if exceptions are possible
noexcept(foo()); // -> true
// If constructor of that object can throw an exception, noexcept() operator will return false
noexcept(foo(object{})); // -> false
```