#pragma once
#include <string>

/**
 * Small wrapper for file descriptors. Makes sure that those file descriptors
 * are not copied across source code (so we can avoid calling close() twice) and
 * automatically closes current file descriptor when it's out of scope.
 */
struct FileDescriptor {

  explicit FileDescriptor(int);

  /**
   * Duplicates other file descriptor using dup() system call
   * @param other  - other file desriptor
   */
  FileDescriptor(const FileDescriptor& other);

  /**
   * Closes current file descriptor and
   * duplicates other file descriptor using dup() system call
   * @param other  - other file descriptor.
   */
  FileDescriptor& operator=(const FileDescriptor& other);

  /**
   * Takes file descriptor from other file descriptor.
   * @param other - other file descriptor
   */
  FileDescriptor(FileDescriptor&& other) noexcept;

  /**
   * Closes current file descriptor and
   * takes file descriptor from other file descriptor
   * @param other - other file descriptor
   */
  FileDescriptor& operator=(FileDescriptor&& other) noexcept;

  /**
   * Calls fcntl() function to retrieve file status flags
   * @return file status flags
   */
  [[nodiscard]] int get_flags() const;

  /**
   * Duplicates current file descriptor
   * @return new file descriptor
   */
  [[nodiscard]] FileDescriptor duplicate() const;

  /**
   * @return true if file descriptor is not equal to -1
   */
  [[nodiscard]] bool is_valid() const;

  /**
   * @return true if file descriptor is equal to -1
   */
  [[nodiscard]] bool is_invalid() const;

  /**
   * Duplicates current file descriptor and assigns it specified file descriptor.
   * (same as calling dup2(this.fd, new_fd.fd))
   * @param new_fd - file descriptor that will be assigned to the duplicate of the current file descriptor
   * @return new file descriptor
   */
  FileDescriptor duplicate(FileDescriptor&& new_fd) const;

  /**
   * O_SYNC or synchronized writes means that seek and write will be one atomic operation.
   * @return true if writes are synchronized
   */
  [[nodiscard]] bool is_write_sync() const;

  // TODO:
  //  Method for working with file status flags
  //  * is_write_only()
  //  * is_read_write()
  //  * set_append()
  //  * set_nonblock()
  //  * set_noatime()
  //  * set_async()
  //  * set_direct()

  /**
   * Explicitly closes current file descriptor. Call this method if you want
   * to close the file descriptor early. Otherwise, destructor will call this method anyway.
   */
  void close();

  /**
   * Calls close() to close this file descriptor
   */
  ~FileDescriptor();

  int fd;
};
