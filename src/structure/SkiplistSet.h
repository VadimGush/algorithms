#pragma once
#include <utility>
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
      nodes.push_back(nullptr);
    }

    explicit Node(const T& value) {
      value.value = value;
      nodes.push_back(nullptr);
    }

    explicit Node(T&& value) {
      value.value = std::move(value);
      nodes.push_back(nullptr);
    }

    [[nodiscard]] size_t height() const {
      return nodes.size();
    }

    V<T> value{0};
    Vector<Node*> nodes{};
  };

  /**
   * Implementation of Set based on skiplist structure.
   * @tparam T - type of stored values.
   */
  template <class T>
  class SkiplistSet {
  public:
    using N = Node<T>;

    SkiplistSet() {
      sentinel_ = new N{};
    }

    [[nodiscard]] size_t size() const {
      return size_;
    }

    // finds min y which is >= x
    N* findPredNode(const T& value) {
      auto* u = sentinel_;
      size_t r = sentinel_->height() - 1;
      while (r >= 0) {
        if (u->nodes.get(r) != nullptr && u->nodes.get(r).value < value) {
          u = u->nodes.get(r);
        }
        r -= 1;
      }
      return u;
    }

    std::optional<T> find(const T& value) {
      N* node = findPredNode(value);
      if (node->nodes.get(0) == nullptr) {
        return {};
      }
      return node->nodes.get(0).value;
    }

    ~SkiplistSet() {
      // sentient doesn't hold any values, so we're immediately skip it
      if (sentinel_->nodes.size() == 0) {
        delete sentinel_;
        return;
      }
      auto* current = sentinel_->nodes.get(0);
      delete sentinel_;

      while (current != nullptr) {
        auto& nodes = current->nodes;
        if (nodes.size() == 0) {
          delete current;
          break;
        }

        auto* next = nodes.get(0);
        // union requires to explicitly call destructor
        current->value.value.~T();
        delete current;
        current = next;
      }
    }

  private:
    size_t size_ = 0;
    N* sentinel_;

    /**
     * Generates a random number and counts how many trailing 1s it has.
     * Why don't we just generate some random number? Because this method gives us
     * random numbers with different distribution (where large numbers are more unlikely).
     *
     * @return random number
     */
    int pickHeight() {
      const int z = rand();
      int k = 0;
      int m = 1;
      while ((z & m) != 0) { k++; m <<= 1; }
      return k;
    }

  };
}


