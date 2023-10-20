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
    class vector {
    public:
        using T = typename std::remove_cv<I>::type;

        vector(): vector(INITIAL_CAPACITY) {}

        vector(const std::initializer_list<I> l): vector(l.size()) {
            std::for_each(l.begin(), l.end(), [this](const auto& i){ push_back(i); });
        }

        explicit vector(const size_t capacity): size_(0) {
            resize_to(capacity);
        }

        vector(const vector<T>& other): size_(other.size_) {
            resize_to(other.size_);
            for (size_t id = 0; id < other.size_; id++) {
                data_[id] = other.data_[id];
            }
        }

        explicit vector(vector<T>&& other) noexcept : size_(other.size_) {
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        vector& operator=(const vector<T>& other) {
            if (&other == this) return *this;

            size_ = other.size_;
            resize_to(other.size_);
            for (size_t id = 0; id < other.size_; id++) {
                data_[id] = other.data_[id];
            }
            return *this;
        }

        vector& operator=(vector<T>&& other) noexcept {
            if (&other == this) return *this;

            // Remove current data completely
            free_data();

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        /**
         * Insert element at the end of the array
         */
        template <class V = T>
        void push_back(V&& value) {
            insert(size_, std::forward<V>(value));
        }

        /**
         * Insert element at the given position and shift all which further
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
         * Get the element from the array by id
         */
		std::optional<T> get(const size_t& id) const {
			return this->operator[](id);
        }

        /**
         * Removes element from the end of the array and returns it
         */
        std::optional<T> pop_back() {
            return remove(size_ - 1);
        }

		std::optional<T> operator[](const size_t i) const {
			if (i < size_ && i >= 0) {
				return data_[i];
			}
			return {};
		}

        /**
         * Removes element from the given position and returns it
         */
        std::optional<T> remove(const size_t id) {
            if (id >= size_) return {};

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

        bool contains(const T& element) const {
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

        [[nodiscard]] size_t size() const {
            return size_;
        }

        ~vector() { free_data(); }

    private:
        T* data_ = nullptr;
        size_t size_ = 0;
        size_t capacity_ = 0;

        /**
         * Calls destructors for all elements and deallocates memory
         */
        void free_data() {
            for (size_t i = 0; i < size_; i++) { data_[i].~T(); }
            free(data_);
            capacity_ = 0;
            size_ = 0;
        }

        /**
         * Increases capacity if we're out of capacity and decreases capacity
         * if we have to little elements (in order to avoid wasting memory)
         */
        void resize() {
            if (size_ == capacity_) resize_to(capacity_ * 2);
            if (size_ * 3 < capacity_) resize_to(capacity_ / 2);
        }

        /**
         * Resize array to the given capacity.
         */
        void resize_to(const size_t capacity) {
            if (capacity <= size_) { return; }

            T* const new_data = static_cast<T*>(calloc(capacity, sizeof(T)));
            for (size_t id = 0; id < size_; id++) {
                new_data[id] = std::move(data_[id]);
            }
            free(data_);
            data_ = new_data;
            capacity_ = capacity;
        }

    };

}

