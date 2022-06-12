# Exceptions

The main things you need to remember about exceptions:
```c++
try {
  // you can throw anything
  throw 3;            // int literal
  throw object{};     // any object
  throw new object{}; // ptr to object
}
// catch works only with exact type
// (except for base classes)
// order DOES matter
catch (T e) {}        // catch by value
catch (const T& e) {} // catch by const reference
catch (T* e) {}       // catch by pointer
catch (...) {}        // will catch anything
```

`noexcept` keyword:
```c++
// noexcept - promise to the compiler
// that we will not throw exceptions
void foo() noexcept;
```

You can detect if certain function is `noexcept`:
```c++
// Special operator that returns true if case provided <expr> will not throw exceptions (it's noexcept)
// or false if exceptions are possible
noexcept(foo()); // -> true
// If constructor of that object can throw an exception, noexcept() operator will return false
noexcept(foo(object{})); // -> false
```