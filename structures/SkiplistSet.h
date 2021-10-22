#pragma once
#include <utility>
#include <array>
#include "Vector.h"

namespace gush {

  template <class T>
  union V {
    char empty;
    T value;
  };

  template <class T>
  struct Node {
    Node() {
      nodes_.push_back(nullptr);
    }

    explicit Node(const T& value) {
      value_.value = value;
      nodes_.push_back(nullptr);
    }

    void setHeight(const size_t height) {
      size_t size = nodes_.size();
      for (size_t i = 0; i < (height - size); i++) {
        nodes_.push_back(nullptr);
      }
    }

    [[nodiscard]] size_t height() const {
      return nodes_.size();
    }

    V<T> value_{0};
    Vector<Node*> nodes_{};
  };

  template <class T>
  struct sl_iterator{
    using N = Node<T>;
    explicit sl_iterator(N* const n): current_(n) {};

    sl_iterator& operator++() {
      if (current_ != nullptr) { current_ = current_->nodes_.get(0); }
      return *this;
    }

    bool operator!=(const sl_iterator& other) {
      return other.current_ != current_;
    }

    const T& operator*() {
      return current_->value_.value;
    }

    N* current_ = nullptr;
  };

  /**
   * Implementation of Set based on skiplist structures.
   * @tparam T - type of stored values.
   */
  template <class T>
  class SkiplistSet {
  public:
    using N = Node<T>;

    SkiplistSet() {
      sentinel_ = new Node<T>{};
      sentinel_->setHeight(32);
    }

    [[nodiscard]] size_t size() const {
      return size_;
    }

    /**
     * Inserts value to the set.
     * Time complexity: O(logN)
     * @param value - value to insert
     */
    void add(const T& value) {
      std::array<N*, 32> stack;
      N* u = sentinel_;
      size_t r = sentinel_->height() - 1;
      while (true) {
        while (true) {
          auto& next = u->nodes_.get(r);
          if (next == nullptr) break;
          if (next->value_.value == value) { return; }
          if (next->value_.value < value) { u = next; } else { break; }
        }
        stack[r] = u;
        if (r == 0) { break; }
        r -= 1;
      }

      N* n = new Node<T>{value};
      const size_t height = pickHeight();
      n->setHeight(height);
      for (int i = 0; i < height; i++) {
        n->nodes_.get(i) = stack[i]->nodes_.get(i);
        stack[i]->nodes_.get(i) = n;
      }
    }

    /**
     * Checks if set contains some value
     * Time complexity: O(logN)
     * @param value value to check
     * @return true if contains, otherwise false
     */
    bool contains(const T& value) {
      N* node = findPredNode(value);
      if (node->nodes_.get(0) == nullptr) { return false; }
      return node->nodes_.get(0).value_.value == value;
    }

    sl_iterator<T> begin() {
      const auto& next = sentinel_->nodes_.get(0);
      if (next != nullptr) { return sl_iterator<T>{next}; }
      return sl_iterator<T>{nullptr};
    }

    sl_iterator<T> end() {
      return sl_iterator<T>{nullptr};
    }

    ~SkiplistSet() {
      // sentinel doesn't hold any values, so we're immediately skip it
      if (sentinel_->nodes_.size() == 0) {
        delete sentinel_; return;
      }
      auto* current = sentinel_->nodes_.get(0);
      delete sentinel_;

      while (current != nullptr) {
        auto& nodes = current->nodes_;
        if (nodes.size() == 0) {
          delete current;
          break;
        }

        auto* next = nodes.get(0);
        // union requires to explicitly call destructor
        current->value_.value.~T();
        delete current;
        current = next;
      }
    }

  private:
    size_t size_ = 0;
    N* sentinel_;

    N* findPredNode(const T& value) {
      auto* u = sentinel_;
      size_t r = sentinel_->height() - 1;
      while (true) {
        while (true) {
          auto& next = u->nodes.get(r);
          if (next == nullptr) { break; }
          if (next->value_.value < value) { u = next; } else { break; }
        }
        if (r == 0) break;
        r -= 1;
      }
      return u;
    }

    /**
     * Generates a random number and counts how many trailing 1s it has.
     * Why don't we just generate some random number? Because this method gives us
     * random numbers with different distribution (where large numbers are more unlikely).
     *
     * Performance of skiplist depends on distribution of random numbers from this function.
     *
     * @return random number
     */
    int pickHeight() {
      const int z = rand();
      int k = 0;
      int m = 1;
      while ((z & m) != 0) { k++; m <<= 1; }
      if (k == 0) { k = 1; }
      return k;
    }

  };
}


