#pragma once
#include "Vector.h"
#include <optional>

namespace gush {

  /**
   * Stack implementation based on dynamic array.
   * @tparam T - type of stored values.
   */
  template <class T>
  class ArrayStack {
  public:

    /**
     * Inserts value at the front of the stack.
     * Time complexity: amortized O(1)
     * @param value - value to insert
     */
    template <class U = T>
    void push(U&& value){
      data_.push_back(std::forward<U>(value));
    }

    /**
     * Removes value from the front of the stack.
     * Time complexity: amortized O(1)
     * @return - removed value
     */
    std::optional<T> pop() {
      return data_.pop_back();
    }

    const T* begin() const {
      return data_.begin();
    }

    const T* end() const {
      return data_.end();
    }

    [[nodiscard]] size_t size() const {
      return data_.size();
    }

  private:
    Vector<T> data_;
  };

}

