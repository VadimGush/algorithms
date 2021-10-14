#pragma once

namespace gush {

  template <class T>
  struct list_node_ {
    list_node_<T>* prev = nullptr;
    list_node_<T>* next = nullptr;
    T value;

    explicit list_node_(const T& value): value(value) {}
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

