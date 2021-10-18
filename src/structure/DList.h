#pragma once

namespace gush {

  template <class T>
  struct list_node_ {
    using Node = list_node_<T>;
    Node* prev = nullptr;
    Node* next = nullptr;
    T value;

    explicit list_node_(const T& value, Node* prev, Node* next)
      : value(value), prev(prev), next(next) {}
  };

  template <class T>
  class iterator {
  public:
    using Node = list_node_<T>;

    explicit iterator(const Node* ptr): current_(ptr) {}

    bool operator!=(const iterator<T>& other) {
      return other.current_ != current_;
    }

    iterator& operator++() {
      if (current_ == nullptr) {
        return *this;
      }
      current_ = current_->next;
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
  // TODO: Add support for non-copy objects (like unique_ptr<>)
  template <class T>
  class DList {
  public:
    using Node = list_node_<T>;
    using Iterator = iterator<T>;

    DList() =default;

    void push_back(const T& value) {
      Node* const node = new Node{value, end_, nullptr};
      if (end_ != nullptr) {
        // DList is not empty
        end_->next = node;
      } else {
        // DList is empty
        begin_ = node;
      }
      size_ += 1;
      end_ = node;
    }

    void push_front(const T& value) {
      Node* const node = new Node{value, nullptr, begin_};
      if (begin_ != nullptr) {
        // DList is empty
        begin_->prev = node;
      } else {
        // DList is empty
        end_ = node;
      }
      size_ += 1;
      begin_ = node;
    }

    std::optional<T> pop_front() {
      if (size_ == 0) {
        return {};
      }

      const Node* current = begin_;
      if (size_ == 1) {
        begin_ = nullptr;
        end_ = nullptr;
      } else {
        begin_ = current->next;
        begin_->prev = nullptr;
      }
      const T result = current->value;
      delete current;
      return result;
    }

    std::optional<T> pop_back() {
      if (size_ == 0) {
        return {};
      }

      const Node* current = end_;
      if (size_ == 1) {
        end_ = nullptr;
        begin_ = nullptr;
      } else {
        end_ = current->prev;
        end_->next = nullptr;
      }
      const T result = current->value;
      delete current;
      return result;
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

