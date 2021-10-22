#pragma once
#include <optional>
#include <utility>

namespace gush {

  template <class T>
  struct list_node_ {
    using Node = list_node_<T>;
    Node* prev = nullptr;
    Node* next = nullptr;
    T value;

    template <class U = T>
    list_node_(U&& value, Node* prev, Node* next)
    : value(std::forward<U>(value)), prev(prev), next(next) {}

  };

  template <class T>
  class dlist_iterator {
  public:
    using Node = list_node_<T>;

    explicit dlist_iterator(const Node* ptr): current_(ptr) {}

    bool operator!=(const dlist_iterator<T>& other) {
      return other.current_ != current_;
    }

    dlist_iterator& operator++() {
      if (current_ != nullptr) { current_ = current_->next; }
      return *this;
    }

    const T& operator*() {
      return current_->value;
    }

  private:
    const Node* current_;
  };

  /**
   * Doubly linked DList.
   * @tparam T - type of stored values.
   */
  template <class T>
  class DList {
  public:
    using Node = list_node_<T>;
    using Iterator = dlist_iterator<T>;

    DList() =default;

    DList(std::initializer_list<T> values) {
      for (const auto& value : values) { push_back(value); }
    }

    /**
     * Inserts a value at the and of list
     * Time complexity: O(1)
     * @param value - value to insert
     */
    template <class U = T>
    void push_back(U&& value) {
      auto* node = new Node{std::forward<U>(value), end_, nullptr};
      if (end_ != nullptr) {
        end_->next = node;
      } else {
        begin_ = node;
      }
      size_ += 1;
      end_ = node;
    }

    /**
     * Inserts a value at the beginning of the list
     * Time complexity: O(1)
     * @param value - value to insert
     */
    template <class U = T>
    void push_front(U&& value) {
      auto* node = new Node{std::forward<U>(value), nullptr, begin_};
      if (begin_ != nullptr) {
        begin_->prev = node;
      } else {
        end_ = node;
      }
      size_ += 1;
      begin_ = node;
    }

    /**
     * Removes a value from the beginning of the list and returns it.
     * @return optional with value if list is not empty, otherwise empty optional
     */
    std::optional<T> pop_front() {
      if (size_ == 0) { return {}; }

      Node* current = begin_;
      if (size_ == 1) {
        begin_ = nullptr;
        end_ = nullptr;
      } else {
        begin_ = current->next;
        begin_->prev = nullptr;
      }
      size_ -= 1;
      T result = std::move(current->value);
      delete current;
      return std::move(result);
    }

    /**
     * Removes a value from the end of the list and returns it.
     * @return optional with value if list is not empty, otherwise empty optional
     */
    std::optional<T> pop_back() {
      if (size_ == 0) {
        return {};
      }

      Node* current = end_;
      if (size_ == 1) {
        end_ = nullptr;
        begin_ = nullptr;
      } else {
        end_ = current->prev;
        end_->next = nullptr;
      }
      size_ -= 1;
      T result = std::move(current->value);
      delete current;
      return std::move(result);
    }

    [[nodiscard]] size_t size() const {
      return size_;
    }

    Iterator begin() {
      return Iterator{begin_};
    }

    Iterator end() {
      return Iterator{nullptr};
    }

    ~DList() {
      Node* current_node = begin_;
      while (current_node != nullptr) {
        Node* next = current_node->next;
        delete current_node;
        current_node = next;
      }
    }

  private:
    Node* begin_ = nullptr;
    Node* end_ = nullptr;
    size_t size_ = 0;
  };
}

