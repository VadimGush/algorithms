#pragma once
#include <iostream>
#include <utility>
#include "Vector.h"

namespace gush {

  template <class T>
  class ArrayDeque;


  /**
   * Deque based on dynamic array
   * @tparam T - type of stored values.
   */
  template <class T>
  class ArrayDeque {
  public:

    struct Iterator {
      Iterator(const ArrayDeque<T>& queue, const size_t id): queue_(queue), id_(id) {}

      void operator++() {
        id_ += 1;
      }

      bool operator!=(const Iterator iterator) {
        return iterator.id_ != id_;
      }

      const T& operator*() {
        const size_t index = (queue_.head_ + id_) % queue_.capacity_;
        return queue_.data_[index];
      }

      const ArrayDeque<T>& queue_;
      size_t id_;
    };

    ArrayDeque() {
      resizeTo(capacity_);
    }

    std::optional<T> pop_front() {
      if (size_ == 0) {
        return {};
      }
      const auto index = head_;
      head_ = (head_ + 1) % capacity_;
      size_ -= 1;
      return {std::move(data_[index])};
    }

    std::optional<T> pop_back() {
      if (size_ == 0) {
        return {};
      }
      const auto index = (head_ + size_ - 1) % capacity_;
      size_ -= 1;
      return {std::move(data_[index])};
    }

    template <class V = T>
    void push_back(V&& value) {
      if (size_ == capacity_) {
        resizeTo(capacity_ * 2);
      }
      const auto index = (head_ + size_) % capacity_;
      this->data_[index] = std::forward<V>(value);
      size_ += 1;
    }

    template <class V = T>
    void push_front(V&& value) {
      if (size_ == capacity_) {
        resizeTo(capacity_ * 2);
      }
      head_ -= 1;
      if (head_ < 0) { head_ = capacity_ - 1; }
      this->data_[head_] = std::forward<V>(value);
      size_ += 1;
    }

    Iterator begin() {
      return {*this, 0};
    }

    Iterator end() {
      return {*this, size_};
    }

    ~ArrayDeque() {
      // we need to call destructors for all initialized values
      // before deallocating memory
      for (auto& element : *this) { element.~T(); }
      free(data_);
      size_ = 0;
      head_ = 0;
      capacity_ = 0;
    }

  private:
    size_t size_ = 0;
    size_t head_ = 0;
    size_t capacity_ = 4;
    T* data_;

    void resizeTo(const size_t capacity) {
      T* const new_data = static_cast<T*>(malloc(sizeof(T) * capacity));

      for (size_t i = 0; i < size_; i++) {
        const size_t index = (head_ + i) % this->capacity_;
        new_data[i] = std::move(this->data_[index]);
      }

      delete[] this->data_;
      this->data_ = new_data;
      this->capacity_ = capacity;
      head_ = 0;
    }

  };


}