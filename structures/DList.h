#pragma once
#include <optional>
#include <utility>

namespace gush {

  /**
   * Doubly linked DList.
   * @tparam T - type of stored values.
   */
  template <class T>
  class DList {

    struct node {
      node* prev = nullptr;
      node* next = nullptr;
      T value;

      template <class U = T>
      node(U&& value, node* const prev, node* const next)
      : value(std::forward<U>(value)), prev(prev), next(next) {}
    };

    struct iterator {
      explicit iterator(const node* ptr): current_(ptr) {}

      bool operator!=(const iterator& other) {
        return other.current_ != current_;
      }

      iterator& operator++() {
        if (current_ != nullptr) { current_ = current_->next; }
        return *this;
      }

      const T& operator*() {
        return current_->value;
      }

      const node* current_;
    };

  public:

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
      auto* n = new node{std::forward<U>(value), end_, nullptr};
      if (end_ != nullptr) {
        end_->next = n;
      } else {
        begin_ = n;
      }
      size_ += 1;
      end_ = n;
    }

    /**
     * Inserts a value at the beginning of the list
     * Time complexity: O(1)
     * @param value - value to insert
     */
    template <class U = T>
    void push_front(U&& value) {
      auto* n = new node{std::forward<U>(value), nullptr, begin_};
      if (begin_ != nullptr) {
        begin_->prev = n;
      } else {
        end_ = n;
      }
      size_ += 1;
      begin_ = n;
    }

    /**
     * Removes a value from the beginning of the list and returns it.
     * @return optional with value if list is not empty, otherwise empty optional
     */
    std::optional<T> pop_front() {
      if (size_ == 0) { return {}; }

      node* current = begin_;
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

      node* current = end_;
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

    iterator begin() {
      return iterator{begin_};
    }

    iterator end() {
      return iterator{nullptr};
    }

    ~DList() {
      node* current_node = begin_;
      while (current_node != nullptr) {
        node* next = current_node->next;
        delete current_node;
        current_node = next;
      }
    }

  private:
    node* begin_ = nullptr;
    node* end_ = nullptr;
    size_t size_ = 0;
  };
}

