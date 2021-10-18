#pragma once
#include "Vector.h"
#include <optional>

namespace gush {

  /**
   * Stack implementation based on dynamic array.
   * @tparam T - type of stored values.
   */
  // TODO: Add support for non-copy objects (like unique_ptr<>)
  template <class T>
  class ArrayStack {
  public:

    void push(const T& value){
      data_.push_back(value);
    }

    const T* begin() const {
      return data_.begin();
    }

    const T* end() const {
      return data_.end();
    }

    std::optional<T> pop() {
      return data_.pop_back();
    }

    [[nodiscard]] size_t size() const {
      return data_.size();
    }

  private:
    Vector<T> data_;
  };

}

