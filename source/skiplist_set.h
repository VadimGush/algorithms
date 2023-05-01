#pragma once
#include <utility>
#include <array>
#include "vector.h"

namespace gush {

    static constexpr int MAX_HEIGHT = 32;

    template <class T>
    union V {
        char empty;
        T value;
    };

    /**
     * Implementation of set based on skiplist structure.
     */
    template <class T>
    class skiplist_set {
    public:

        struct node {
            node() {
                nodes_.push_back(nullptr);
            }

            explicit node(const T& value) {
                value_.value = value;
                nodes_.push_back(nullptr);
            }

            void setHeight(const size_t height) {
                size_t size = nodes_.size();
                for (size_t i = 0; i < (height - size); i++) {
                    nodes_.push_back(nullptr);
                }
            }

            [[nodiscard]] size_t height() const {
                return nodes_.size();
            }

            V<T> value_{0};
            vector<node*> nodes_{};
        };

        using N = node;

        struct iterator {
            explicit iterator(N* const n): current_(n) {};

            iterator& operator++() {
                if (current_ != nullptr) { current_ = current_->nodes_.get(0); }
                return *this;
            }

            bool operator!=(const iterator& other) {
                return other.current_ != current_;
            }

            const T& operator*() {
                return current_->value_.value;
            }

            N* current_ = nullptr;
        };

        skiplist_set() {
            sentinel_ = new N{};
            sentinel_->setHeight(MAX_HEIGHT);
        }

        /**
         * Inserts value to the set.
         * Time complexity:
         *   * Best case: O(logN)
         *   * Worst case: O(N)
         */
        void add(const T& value) {
            std::array<N*, MAX_HEIGHT> stack;
            if (!fill_stack(value, stack, false)) { return; }

            // Create a new node
            N* n = new N{value};
            const size_t height = pick_height();
            n->setHeight(height);
            // Go through stack and set pointers to the new node
            for (int i = 0; i < height; i++) {
                n->nodes_.get(i) = stack[i]->nodes_.get(i);
                stack[i]->nodes_.get(i) = n;
            }
            size_ += 1;
        }

        /**
         * Removes value from the set.
         * Time complexity:
         *   * Best case: O(logN)
         *   * Worst case: O(N)
         */
        void remove(const T& value) {
            std::array<N*, MAX_HEIGHT> stack;
            if (!fill_stack(value, stack, true)) { return; }

            // get pointer to the next node and check if it has required value
            auto* const next = stack[0]->nodes_.get(0);
            if (next == nullptr || next->value_.value != value) { return; }

            // go through every node and replace pointers
            for (size_t i = 0; i < MAX_HEIGHT; i++) {
                if (stack[i]->nodes_.get(i) == next) {
                    stack[i]->nodes_.get(i) = next->nodes_.get(i);
                } else {
                    break;
                }
            }
            delete next;
            size_ -= 1;
        }

        /**
         * Checks if set contains a value
         * Time complexity:
         *   * Best case: O(logN)
         *   * Worst case: O(N)
         */
        [[nodiscard]] bool contains(const T& value) const {
            const N* node = find_prev_node(value);
            if (node->nodes_.get(0) == nullptr) { return false; }
            return node->nodes_.get(0)->value_.value == value;
        }

        [[nodiscard]] size_t size() const {
            return size_;
        }

        iterator begin() {
            const auto& next = sentinel_->nodes_.get(0);
            if (next != nullptr) { return iterator{next}; }
            return iterator{nullptr};
        }

        iterator end() {
            return iterator{nullptr};
        }

        ~skiplist_set() {
            // sentinel doesn't hold any values, so we're immediately skip it
            if (sentinel_->nodes_.size() == 0) {
                delete sentinel_; return;
            }
            auto* current = sentinel_->nodes_.get(0);
            delete sentinel_;

            while (current != nullptr) {
                auto* next = current->nodes_.get(0);
                // union requires to explicitly call destructor
                current->value_.value.~T();
                delete current;
                current = next;
            }
        }

    private:
        size_t size_ = 0;
        N* sentinel_;

        /**
         * Will fill the stack with pointers to nodes in which values are less then specified value.
         * If equals flag contains true, this method will not return in case if node with specified value is found.
         *
         * @param value - specified value
         * @param stack - stack to fill
         * @param equals - if true, then this method will not fail in case if node with specified value is found
         * @return true in case of success and false in case of fail (if collection has node with specified value for example)
         */
        bool fill_stack(const T& value, std::array<N*, MAX_HEIGHT>& stack, const bool equals) {
            N* u = sentinel_;
            size_t depth = MAX_HEIGHT - 1;
            while (true) {
                while (true) {
                    auto *const next = u->nodes_.get(depth);
                    if (next == nullptr) { break; }
                    if (next->value_.value == value) {
                        // when we're removing values, we don't want to return immediately when we found
                        // node with specified value
                        // if we're adding values, then add() should fail if there is already such value in collection
                        if (!equals) { return false; } else { break; }
                    }
                    if (next->value_.value < value) { u = next; } else { break; }
                }
                stack[depth] = u;
                if (depth == 0) { break; }
                depth -= 1;
            }

            return true;
        }

        /**
         * Finds node which has value that is less than specified
         * So the next node either has specified value, or has value which is greater than specified.
         * @param value - specified value
         * @return pointer to that node
         */
        N* find_prev_node(const T& value) {
            auto* u = sentinel_;
            size_t r = sentinel_->height() - 1;
            while (true) {
                while (true) {
                    auto& next = u->nodes_.get(r);
                    if (next == nullptr) { break; }
                    if (next->value_.value < value) { u = next; } else { break; }
                }
                if (r == 0) break;
                r -= 1;
            }
            return u;
        }

        /**
         * Generates a random number and counts how many trailing 1s it has.
         * Why don't we just generate some random number? Because this method gives us
         * random numbers with different distribution (where large numbers are more unlikely).
         *
         * Performance of skiplist depends on distribution of random numbers from this function.
         * TODO: Test distribution of that function
         * @return random number
         */
        int pick_height() {
            const int z = rand();
            int k = 0;
            int m = 1;
            while ((z & m) != 0) { k++; m <<= 1; }
            if (k == 0) { k = 1; }
            return k;
        }

    };
}


