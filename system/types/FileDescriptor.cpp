#include "FileDescriptor.h"
#include "../logging/Logging.h"
#include <unistd.h>
#include <iostream>

FileDescriptor::FileDescriptor(const int fd): fd(fd) {}

FileDescriptor::FileDescriptor(FileDescriptor &&other) noexcept {
  fd = other.fd;
  other.fd = -1;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
  fd = other.fd;
  other.fd = -1;
  return *this;
}

FileDescriptor::~FileDescriptor() {
  if (fd == -1) { return; }
  if (close(fd) == -1) { with_errno() << "Failed to close file descriptor: " << fd << std::endl; }
}
