#pragma once
#include <cstdlib>
#include <vector>

namespace gush {

    template<size_t T>
    class block_storage;

    using BS1 = block_storage<1024>;
    using BS8 = block_storage<8 * 1024>;
    using BS16 = block_storage<16 * 1024>;
    using BS32 = block_storage<32 * 1024>;
    using BS64 = block_storage<64 * 1024>;
    using BS128 = block_storage<128 * 1024>;

    /**
     * Stores blocks of binary data in linked list.
     * Designed for reading streams of data (of unknown size).
     *
     * For example, let's say you want to read stream of data from a file and then
     * convert that data to plain array of bytes. You can do it like that:
     *
     * auto bs = block_storage<1024>::fill_from([&](char* p, size_t s){ read(fd, p, s); });
     * char* data = bs.to_plain().data();
     *
     * @tparam T - size of the single block.
     */
    template<size_t T>
    class block_storage {
    public:

        template<size_t S>
        struct node {
            node *next = nullptr;
            size_t committed = 0;
            char data[S];
        };

        struct block {
            char *data;
            size_t available;
        };

        using N = node<T>;

        block_storage() : head_(new N{}), current_(head_) {}

        /**
         * Creates new block_storage and fills it using provided function. Read fill() docs for more info.
         *
         * @param fill_function - function to fill new block_storage
         * @return new block_storage filled with data
         */
        static block_storage fill_from(const std::function<size_t(char *, size_t)> &fill_function) {
            block_storage bs{};
            bs.fill(fill_function);
            return bs;
        }

        /**
         * Creates array of bytes from block_storage. After call to this function block_storage will be deleted.
         *
         * @param bs - block storage
         * @return array of data from block_storage
         */
        std::vector<char> to_plain() && {
            std::vector<char> data(this->bytes_);
            size_t pos = 0;
            this->for_each([&](const char *block, size_t size) {
                memcpy(&(data[pos]), block, size);
                pos += size;
            });
            return data;
        }

        /**
         * Creates a string from block_storage (assuming that block_storage stores text data). After call to this function
         * block_storage will be deleted.
         *
         * @param bs - block storage
         * @return string containing text from block_storage
         */
        std::string to_string() && {
            auto data = std::move(*this).to_plain();
            return std::string{data.data(), data.size()};
        }

        block_storage(const block_storage &) = delete;

        block_storage &operator=(const block_storage &) = delete;

        block_storage(block_storage &&other) noexcept {
            bytes_ = other.bytes_;
            current_ = other.current_;
            head_ = other.head_;
            other.head_ = nullptr;
        }

        block_storage &operator=(block_storage &&other) noexcept {
            bytes_ = other.bytes_;
            current_ = other.current_;
            head_ = other.head_;
            other.head_ = nullptr;
        }

        /**
         * Returns block structure which contains a pointer to the block of available data and how much
         * bytes you can write to it. After write is completed you should call commit() in order
         * to inform block_storage on how much data was written.
         *
         * @return currently active block of data
         */
        block get_block() {
            const auto committed = current_->committed;
            const auto b = block{&current_->data[committed], T - committed};
            return b;
        }

        /**
         * Commit N bytes to currently active block of data. If the current block is
         * full, then new block will be created.
         *
         * @param bytes - how much data was written to the current block
         */
        void commit(const size_t bytes) {
            bytes_ += bytes;
            current_->committed += bytes;
            if (current_->committed == T) {
                auto *const n = new N{};
                current_->next = n;
                current_ = n;
            }
        }

        /**
         * Fills block_storage with data by writing chunks of data to every block. Returns
         * when provided function returns 0.
         *
         * For example to fill block_storage with data from a file you can write code like that (assuming
         * fd is a file descriptor to the file):
         * block_storage<1024> bs{};
         * bs.fill([&](char* ptr, size_t size){ read(fd, ptr, size); })
         *
         * @param consumer - function that fills block_storage with data. Should accept a pointer
         * to the block of data, size of that block and should return how much bytes was written to that block.
         */
        void fill(const std::function<size_t(char *, size_t)> &consumer) {
            while (true) {
                auto block = get_block();
                auto bytes = consumer(block.data, block.available);
                if (bytes == 0) { break; }
                commit(bytes);
            }
        }

        /**
         * Iterates over all block of data.
         *
         * @param consumer - function which takes a pointer to the block of data and amount of data in this block
         */
        void for_each(const std::function<void(const char *, size_t)> &consumer) const {
            N *current = head_;
            while (current != nullptr) {
                consumer(current->data, current->committed);
                current = current->next;
            }
        }

        ~block_storage() {
            N *current = head_;
            while (current != nullptr) {
                N *next = current->next;
                delete current;
                current = next;
            }
        }

    private:
        size_t bytes_ = 0;
        N *head_;
        N *current_;
    };
}