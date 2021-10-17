#pragma once

#include <utility>
#include <optional>
#define INITIAL_CAPACITY 4

namespace gush {

  /**
   * Simple Vector implementation.
   * @tparam I - type of stored values.
   */
  template<class I>
  class Vector {
  public:
    using T = typename std::remove_cv<I>::type;

    Vector(): Vector(INITIAL_CAPACITY) {}

    Vector(const std::initializer_list<I> elements): Vector(elements.size()) {
      for (const auto& item : elements) {
        push_back(item);
      }
    }

    explicit Vector(const size_t capacity): size_(0) {
      resize_to(capacity);
    }

    Vector(const Vector<T>& other): size_(other.size_) {
      resize_to(other.size_);
      for (size_t id = 0; id < other.size_; id++) {
        data_[id] = other.data_[id];
      }
    }

    explicit Vector(Vector<T>&& other) noexcept : size_(other.size_) {
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
    }

    Vector& operator=(const Vector<T>& other) {
      if (&other == this) return *this;

      size_ = other.size_;
      resize_to(other.size_);
      for (size_t id = 0; id < other.size_; id++) {
        data_[id] = other.data_[id];
      }
      return *this;
    }

    Vector& operator=(Vector<T>&& other) noexcept {
      if (&other == this) return *this;

      free(data_);
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
    }

    void push_back(const T& value) {
      insert(size_, value);
    }

    void insert(const size_t id, const T& value) {
      if (id > size_) {
        return;
      }

      resize();
      auto insert = value;
      for (size_t i = id; i <= size_; i++) {
        auto old_value = data_[i];
        data_[i] = insert;
        insert = old_value;
      }
      size_ += 1;
    }

    const T* begin() const {
      return &data_[0];
    }

    const T* end() const {
      return &data_[size_];
    }

    std::optional<T> pop_back() {
      resize();
      if (size_ > 0) {
        const T& value = data_[size_ - 1];
        size_ -= 1;
        return value;
      }
      return {};
    }

    T remove(const size_t id) {
      auto result = data_[id];
      for (size_t i = id; i < size_ - 1; i++) {
        data_[i] = data_[i + 1];
      }
      size_ -= 1;
      return result;
    }

    void clear() {
      size_ = 0;
    }

    bool contains(const T& element) {
      for (size_t id = 0; id < size_; id++) {
        if (data_[id] == element) return true;
      }
      return false;
    }

    void invert() {
      for (size_t i = 0; i < size_ / 2; i++) {
        std::swap(data_[i], data_[size_ - 1 - i]);
      }
    }

    void shift_left() {
      if (size_ == 0) return;

      T temp = data_[0];
      for (size_t i = 0; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
      }
      data_[size_ - 1] = temp;
    }

    void shift_right() {
      if (size_ == 0) return;

      T temp = data_[size_ - 1];
      for (size_t i = size_ - 1; i >= 1; --i) {
        data_[i] = data_[i-1];
      }
      data_[0] = temp;
    }

    void insert_sort() {
      for (size_t i = 0; i < size_; i++) {
        for (size_t c = i; c >= 1; c--) {
          if (data_[c] < data_[c - 1])
            std::swap(data_[c], data_[c - 1]);
          else break;
        }
      }
    }

    void choice_sort() {
      for (size_t i = 0; i < size_ - 1; i++) {
        for (size_t c = i + 1; c < size_; c++) {
          if (data_[c] < data_[i])
            std::swap(data_[c], data_[i]);
        }
      }
    }

    [[nodiscard]] size_t size() const {
      return size_;
    }

    ~Vector() {
      free(data_);
      size_ = 0;
      capacity_ = 0;
    }

  protected:
    T* data_;
    size_t size_;
    size_t capacity_;

    /**
     * Checks if capacity of the vector is enough to store one more element.
     * If not, this method will resize capacity of the current vector by allocating more memory.
     *
     * If current number of stored elements is too small, this method will lower capacity of the current vector.
     *
     * @param required_size - number of elements that we want to store.
     */
    void resize() {
      if (size_ == capacity_) {
        resize_to(capacity_ * 2);
      }
      if (size_ * 3 < capacity_) {
        resize_to(capacity_ / 2);
      }
    }

    /**
     * Resizes the vector to required capacity (it can me smaller or larger than current capacity).
     * If specified capacity will be smaller than number of currently stored elements, resize_to will
     * not take place.
     * @param capacity - required capacity for the current vector.
     */
    void resize_to(const size_t capacity) {
      if (capacity <= size_) {
        return;
      }

      T* new_data = static_cast<T*>(malloc(sizeof(T) * capacity));
      for (size_t id = 0; id < size_; id++) {
        new_data[id] = data_[id];
      }
      free(data_);
      data_ = new_data;
      capacity_ = capacity;
    }

  };

}

