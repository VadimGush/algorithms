#ifndef ALGORITHMS_OPTIONAL_H
#define ALGORITHMS_OPTIONAL_H

#include <algorithm>
#include <functional>

template <typename T>
struct Storage {
  char data[sizeof(T)];
};

template <typename T>
class Optional {
public:

  Optional() : present_(false) {}

  template <typename ...Args>
  explicit Optional(Args&& ...args) : present_(true) {
    new (&storage_.data) T(std::forward<Args>(args)...);
  }

  T& get() {
    return *reinterpret_cast<T*>(&storage_.data);
  }

  const T& get() const {
    return *reinterpret_cast<const T*>(&storage_.data);
  }

  bool isPresent() const {
    return present_;
  }

  bool isEmpty() const {
    return !present_;
  }

  operator bool() const {
    return present_;
  }

  void ifPresent(std::function<void(const T&)> function) const {
    if (present_) function(get());
  }

  template <typename U>
  Optional<U> map(std::function<U(const T&)> function) const {
    if (present_) {
      return Optional<U>(function(get()));
    } else {
      return {};
    }
  }

private:
  Storage<T> storage_;
  bool present_;
};

#endif //ALGORITHMS_OPTIONAL_H
