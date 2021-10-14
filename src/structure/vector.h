#pragma once

#include <utility>
#include <optional>
#define INITIAL_CAPACITY 4

namespace gush {

  /**
   * Simple vector implementation.
   * @tparam I - type of stored values.
   */
  template<class I>
  class vector {
  public:
    typedef typename std::remove_cv<I>::type T;

    vector(): vector(INITIAL_CAPACITY) {}

    vector(const std::initializer_list<I> elements): vector(elements.size()) {
      for (const auto& item : elements) {
        push_back(item);
      }
    }

    explicit vector(const size_t capacity): size_(0) {
      resize(capacity);
    }

    vector(const vector<T>& other): size_(other.size_) {
      resize(other.size_);
      for (size_t id = 0; id < other.size_; id++) {
        data_[id] = other.data_[id];
      }
    }

    explicit vector(vector<T>&& other) noexcept : size_(other.size_) {
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
    }

    vector& operator=(const vector<T>& other) {
      if (&other == this) return *this;

      size_ = other.size_;
      resize(other.size_);
      for (size_t id = 0; id < other.size_; id++) {
        data_[id] = other.data_[id];
      }
      return *this;
    }

    vector& operator=(vector<T>&& other) noexcept {
      if (&other == this) return *this;

      free(data_);
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
    }

    void push_back(const T& value) {
      if (size_ == capacity_) {
        allocate_more();
      }
      data_[size_] = value;
      size_ += 1;
    }

    const T* begin() const {
      return &data_[0];
    }

    const T* end() const {
      return &data_[size_];
    }

    std::optional<T> pop_back() {
      if (size_ > 0) {
        T& value = data_[size_ - 1];
        size_ -= 1;

        if (capacity_ > 3 * size_) {
          resize(capacity_ / 2);
        }
        return value;
      }
      return {};
    }

    void remove(const size_t id) {
      for (size_t i = id; i < size_ - 1; i++) {
        data_[i] = data_[i + 1];
      }
      size_ -= 1;
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

    void insert(const size_t id, const T& element) {
      if (id == size_) {
        push_back(element);
        return;
      }

      if (size_ == capacity_) {
        allocate_more();
      }

      T current = element;
      for (size_t i = id; i <= size_; ++i) {
        T temp = data_[i];
        data_[i] = current;
        current = temp;
      }
      size_ += 1;
    }

    [[nodiscard]] size_t size() const {
      return size_;
    }

    ~vector() {
      free(data_);
      size_ = 0;
      capacity_ = 0;
    }

  private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize(const size_t capacity) {
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

    void allocate_more() {
      resize(capacity_ * 2);
    }
  };

}

