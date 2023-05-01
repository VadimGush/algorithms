# Terminology

#### Kalb line
When writing exception safe method you need to be able to draw "Kalb line". Or put it more simply,
you need to divide your code into 2 blocks: one that throws exception but doesn't change class state, and
other that changes state but doesn't throw exceptions.
```c++
// Let's look at push() method for vector class
void push(const T& t) {
  if (used_ == size_) {
    vector tmp{size_ * 2 + 1};
    while (tmp.size() < used_)
      tmp.push(arr_[tmp.size()]);
    tmp.push(t);
    // Above this line invariant of the class is not changed
    // ------------------ KALB LINE ------------------------
    // Below this line there are no exception
    swap(*this, tmp);
    return;
  }
}
  
```