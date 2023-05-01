#pragma once
#include <iostream>
#include <utility>
#include "vector.h"

namespace gush {

    /**
     * Deque based on dynamic array.
     *
     * @tparam T - type of stored values.
     */
    template <class T>
    class array_deque {

        struct iterator {
            iterator(const array_deque<T>& queue, const size_t id): queue_(queue), id_(id) {}

            void operator++() {
                id_ += 1;
            }

            bool operator!=(const iterator iterator) {
                return iterator.id_ != id_;
            }

            const T& operator*() {
                const size_t index = (queue_.head_ + id_) % queue_.capacity_;
                return queue_.data_[index];
            }

            const array_deque<T>& queue_;
            size_t id_;
        };

    public:

        array_deque() {
            resize_to(capacity_);
        }

        /**
         * Removes a value from the the front of the deque
         * Time complexity: O(1)
         *
         * @return optional with a value if the deque is not empty, otherwise an empty optional
         */
        std::optional<T> pop_front() {
            if (size_ == 0) {
                return {};
            }
            const auto index = head_;
            head_ = (head_ + 1) % capacity_;
            size_ -= 1;
            return {std::move(data_[index])};
        }

        /**
         * Removes a value from the back of the deque
         * Time complexity: O(1)
         *
         * @return optional with a value if the deque is not empty, otherwise an empty optional
         */
        std::optional<T> pop_back() {
            if (size_ == 0) {
                return {};
            }
            const auto index = (head_ + size_ - 1) % capacity_;
            size_ -= 1;
            return {std::move(data_[index])};
        }

        /**
         * Inserts a value at the back of the deque
         * Time complexity: O(1)
         *
         * @param value  - value to insert
         */
        template <class V = T>
        void push_back(V&& value) {
            if (size_ == capacity_) {
                resize_to(capacity_ * 2);
            }
            const auto index = (head_ + size_) % capacity_;
            this->data_[index] = std::forward<V>(value);
            size_ += 1;
        }

        /**
         * Inserts a value at the front of the deque
         * Time complexity: O(1)
         *
         * @param value - value to insert
         */
        template <class V = T>
        void push_front(V&& value) {
            if (size_ == capacity_) {
                resize_to(capacity_ * 2);
            }
            head_ -= 1;
            if (head_ < 0) { head_ = capacity_ - 1; }
            this->data_[head_] = std::forward<V>(value);
            size_ += 1;
        }

        /**
         * Checks if collections contains specified value
         * Time complexity: O(N)
         *
         * @param value - value to search for
         * @return true if value is present in the collection
         */
        [[nodiscard]] bool contains(const T& value) const {
            for (const auto& v : *this) {
                if (v == value) { return true; }
            }
            return false;
        }

        iterator begin() {
            return {*this, 0};
        }

        iterator end() {
            return {*this, size_};
        }

        ~array_deque() {
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

        void resize_to(const size_t capacity) {
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