#pragma once
#include <cstdlib>
#include <vector>

namespace gush {

  template<size_t T>
  class BlockStorage;

  using BS1 = BlockStorage<1024>;
  using BS8 = BlockStorage<8 * 1024>;
  using BS16 = BlockStorage<16 * 1024>;
  using BS32 = BlockStorage<32 * 1024>;
  using BS64 = BlockStorage<64 * 1024>;
  using BS128 = BlockStorage<128 * 1024>;

  template<size_t T>
  struct Node {
    Node *next = nullptr;
    size_t committed = 0;
    char data[T];
  };

  struct Block {
    char *data;
    size_t available;
  };

  /**
   * Stores blocks of binary data in linked list.
   * Designed for reading streams of data (of unknown size).
   *
   * For example, let's say you want to read stream of data from a file and then
   * convert that data to plain array of bytes. You can do it like that:
   *
   * auto bs = BlockStorage<1024>::fill_from([&](char* p, size_t s){ read(fd, p, s); });
   * char* data = bs.to_plain().data();
   *
   * @tparam T - size of the single block.
   */
  template<size_t T>
  class BlockStorage {
  public:
    using N = Node<T>;

    BlockStorage() : head_(new N{}), current_(head_) {}

    /**
     * Creates new BlockStorage and fills it using provided function. Read fill() docs for more info.
     *
     * @param fill_function - function to fill new BlockStorage
     * @return new BlockStorage filled with data
     */
    static BlockStorage fill_from(const std::function<size_t(char *, size_t)> &fill_function) {
      BlockStorage bs{};
      bs.fill(fill_function);
      return bs;
    }

    /**
     * Creates array of bytes from BlockStorage. After call to this function BlockStorage will be deleted.
     *
     * @param bs - block storage
     * @return array of data from BlockStorage
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
     * Creates a string from BlockStorage (assuming that BlockStorage stores text data). After call to this function
     * BlockStorage will be deleted.
     *
     * @param bs - block storage
     * @return string containing text from BlockStorage
     */
    std::string to_string() && {
      auto data = std::move(*this).to_plain();
      return std::string{data.data(), data.size()};
    }

    BlockStorage(const BlockStorage &) = delete;

    BlockStorage &operator=(const BlockStorage &) = delete;

    BlockStorage(BlockStorage &&other) noexcept {
      bytes_ = other.bytes_;
      current_ = other.current_;
      head_ = other.head_;
      other.head_ = nullptr;
    }

    BlockStorage &operator=(BlockStorage &&other) noexcept {
      bytes_ = other.bytes_;
      current_ = other.current_;
      head_ = other.head_;
      other.head_ = nullptr;
    }

    /**
     * Returns Block structure which contains a pointer to the block of available data and how much
     * bytes you can write to it. After write is completed you should call commit() in order
     * to inform BlockStorage on how much data was written.
     *
     * @return currently active block of data
     */
    Block get_block() {
      const auto committed = current_->committed;
      const auto block = Block{&current_->data[committed], T - committed};
      return block;
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
     * Fills BlockStorage with data by writing chunks of data to every block. Returns
     * when provided function returns 0.
     *
     * For example to fill BlockStorage with data from a file you can write code like that (assuming
     * fd is a file descriptor to the file):
     * BlockStorage<1024> bs{};
     * bs.fill([&](char* ptr, size_t size){ read(fd, ptr, size); })
     *
     * @param consumer - function that fills BlockStorage with data. Should accept a pointer
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

    ~BlockStorage() {
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