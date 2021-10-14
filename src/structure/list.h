#pragma once

namespace gush {

  template <class T>
  struct list_node_ {
    list_node_<T>* prev = nullptr;
    list_node_<T>* next = nullptr;
    T value;

    explicit list_node_(const T& value): value(value) {}
  };

  template <class T>
  class iterator {
  public:
    explicit iterator(const list_node_<T>* ptr): current_(ptr) {}

    bool operator==(const iterator<T>& other) {
      return other.current_ == current_;
    }

    iterator& operator++() {
      if (current_ == nullptr) {
        return;
      }
      current_ = current_->next;
      return *this;
    }

  private:
    const list_node_<T>* current_;
  };

  /**
   * Doubly linked list.
   * @tparam T - type of stored values.
   */
  template <class T>
  class list {
  public:
    list() =default;

    ~list() {
      auto current_node = begin_;
      while (current_node != nullptr) {
        auto next = begin_->next;
        free(current_node);
        current_node = next;
      }
    }
  private:
    list_node_<T>* begin_ = nullptr;
    list_node_<T>* end_ = nullptr;
    size_t size_ = 0;
  };
}

