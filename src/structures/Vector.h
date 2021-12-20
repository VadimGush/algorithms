#pragma once
#include <utility>
#include <optional>
#include <algorithm>
#define INITIAL_CAPACITY 4

namespace gush {

  /**
   * Dynamically sized array.
   *
   * @tparam I - type of stored values.
   */
  template<class I>
  class Vector {
  public:
    using T = typename std::remove_cv<I>::type;

    Vector(): Vector(INITIAL_CAPACITY) {}

    Vector(const std::initializer_list<I> l): Vector(l.size()) {
      std::for_each(l.begin(), l.end(), [this](const auto& i){ push_back(i); });
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
      other.size_ = 0;
      other.capacity_ = 0;
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

      // Remove current data completely
      freeData();

      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    /**
     * Inserts an element to the end of the vector.
     * Time complexity: O(1)
     *
     * @param value - value to insert
     */
    template <class V = T>
    void push_back(V&& value) {
      insert(size_, std::forward<V>(value));
    }

    /**
     * Inserts a value into the vector
     * Time complexity: O(N - i), where N - number of stored elements, i - position to insert to
     *
     * @param pos - position to insert a value to
     * @param value - value to insert
     */
    template <class V = T>
    void insert(const size_t pos, V&& value) {
      if (pos > size_) { return; }
      resize();

      T insert{std::forward<V>(value)};
      for (size_t i = pos; i <= size_; i++) {
        auto old_value = std::move(data_[i]);
        data_[i] = std::move(insert);
        insert = std::move(old_value);
      }
      size_ += 1;
    }

    /**
     * Returns reference to the element in the vector by id
     * Time complexity: O(1)
     *
     * @param id - id of the element
     * @return const reference to that element
     */
    T& get(const size_t& id) const {
      return data_[id];
    }

    /**
     * Removes element from the end of the vector
     * Time complexity: O(1)
     *
     * @return removed element
     */
    std::optional<T> pop_back() {
      return remove(size_ - 1);
    }

    /**
     * Removes an element from the vector and returns it.
     * Time complexity: O(N - i), where N - number of stored elements, i - position to remove value from
     *
     * @param id - position from which we want to remove a value
     * @return optional with removed value, or empty optional if id out of bound
     */
    std::optional<T> remove(const size_t id) {
      if (id < 0 || id >= size_) return {};
      T&& result = std::move(data_[id]);
      for (size_t i = id; i < size_ - 1; i++) {
        data_[i] = std::move(data_[i + 1]);
      }
      size_ -= 1;
      return std::move(result);
    }

    /**
     * Clears content of the current vector.
     */
    void clear() {
      // don't forget to call destructors
      for (size_t i = 0; i < size_; i++) { data_[i].~T(); }
      size_ = 0;
      resize();
    }

    /**
     * Checks if the vector contains such element
     * Time complexity: O(N), where N - number of stored elements
     *
     * @param element - element to find
     * @return true if this vector contains such element, otherwise false
     */
    bool contains(const T& element) {
      for (size_t id = 0; id < size_; id++) {
        if (data_[id] == element) return true;
      }
      return false;
    }

    const T* begin() const {
      return &data_[0];
    }

    const T* end() const {
      return &data_[size_];
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

    ~Vector() { freeData(); }

  protected:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    /**
     * Calls destructors for all initialized elements and deallocates memory
     */
    void freeData() {
      for (size_t i = 0; i < size_; i++) { data_[i].~T(); }
      free(data_);
      capacity_ = 0;
      size_ = 0;
    }

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
     *
     * @param capacity - required capacity for the current vector.
     */
    void resize_to(const size_t capacity) {
      if (capacity <= size_) { return; }

      T* const new_data = static_cast<T*>(malloc(sizeof(T) * capacity));
      for (size_t id = 0; id < size_; id++) {
        new_data[id] = std::move(data_[id]);
      }
      free(data_);
      data_ = new_data;
      capacity_ = capacity;
    }

  };

}

