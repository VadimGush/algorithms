#pragma once
#include "vector.h"
#include <optional>

namespace gush {

    /**
     * Stack based on dynamic array.
     * @tparam T - type of stored values.
     */
    template <class T>
    class array_stack {
    public:

        /**
         * Inserts value at the front of the stack.
         * Time complexity: O(1)
         */
        template <class U = T>
        void push(U&& value){
            data_.push_back(std::forward<U>(value));
        }

        /**
         * Removes value from the front of the stack.
         * Time complexity: O(1)
         *
         * @return - removed value
         */
        std::optional<T> pop() {
            return data_.pop_back();
        }

        /**
         * Checks if collection contains given value.
         * Time complexity: O(N)
         *
         * @param value - value to search for
         * @return true if collection contains such value, otherwise false
         */
        [[nodiscard]] bool contains(const T& value) const {
            for (const auto& v : *this) {
                if (v == value) { return true; }
            }
            return false;
        }

        const T* begin() const {
            return data_.begin();
        }

        const T* end() const {
            return data_.end();
        }

        [[nodiscard]] size_t size() const {
            return data_.size();
        }

    private:
        vector<T> data_;
    };

}

