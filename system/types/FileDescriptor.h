#pragma once

/**
 * Small wrapper for file descriptors. Makes sure that those file descriptors
 * are not copied across source code (so we can avoid calling close() twice) and
 * automatically closes current file descriptor when it's out of scope.
 */
struct FileDescriptor {
  explicit FileDescriptor(int);
  FileDescriptor(FileDescriptor&& other) noexcept;
  FileDescriptor& operator=(FileDescriptor&& other) noexcept;
  ~FileDescriptor();
  int fd;
};
