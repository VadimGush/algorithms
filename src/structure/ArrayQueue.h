#pragma once
#include <iostream>
#include "Vector.h"

namespace gush {

  template <class T>
  class ArrayQueue;


  /**
   * FIFO queue based on dynamic array
   * @tparam T - type of stored values.
   */
  template <class T>
  class ArrayQueue {
  public:

    struct Iterator {
      Iterator(const ArrayQueue<T>& queue, const size_t id): queue_(queue), id_(id) {}

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

      const ArrayQueue<T>& queue_;
      size_t id_;
    };

    ArrayQueue() {
      data_ = new T[capacity_];
    }

    std::optional<T> pop() {
      if (size_ == 0) {
        return {};
      }
      const auto& result = data_[head_];
      head_ = (head_ + 1) % capacity_;
      size_ -= 1;
      return result;
    }

    void push(const T& value) {
      if (size_ == capacity_) {
        expand();
      }
      const size_t index = (head_ + size_) % capacity_;
      this->data_[index] = value;
      size_ += 1;
    }

    Iterator begin() {
      return {*this, 0};
    }

    Iterator end() {
      return {*this, size_};
    }

  private:
    size_t size_ = 0;
    size_t head_ = 0;

    size_t capacity_ = 4;
    T* data_;

    void expand() {
      const size_t new_capacity = this->capacity_ * 2;
      T* const new_data = new T[new_capacity];

      for (size_t i = 0; i < size_; i++) {
        const size_t index = (head_ + i) % this->capacity_;
        new_data[i] = this->data_[index];
      }

      delete[] this->data_;
      this->data_ = new_data;
      this->capacity_ = new_capacity;
      head_ = 0;
    }

  };


}