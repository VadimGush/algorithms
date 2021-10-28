#include "FileDescriptor.h"
#include "../logging/Logging.h"
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

FileDescriptor::FileDescriptor(const int fd): fd(fd) {}

FileDescriptor::FileDescriptor(FileDescriptor &&other) noexcept {
  fd = other.fd;
  other.fd = -1;
}

FileDescriptor::FileDescriptor(const FileDescriptor& other) {
  fd = dup(other.fd);
}

FileDescriptor& FileDescriptor::operator=(const FileDescriptor& other) {
  close();
  fd = dup(other.fd);
  return *this;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
  close();
  fd = other.fd;
  other.fd = -1;
  return *this;
}

int FileDescriptor::get_flags() const {
  return fcntl(fd, F_GETFL);
}

bool FileDescriptor::is_valid() const {
  return -1 != fd;
}

bool FileDescriptor::is_invalid() const {
  return -1 == fd;
}

bool FileDescriptor::is_write_sync() const {
  return get_flags() & O_SYNC;
}

/*
void FileDescriptor::set_flags(const int flags) {
  fcntl(fd, F_SETFL, flags);
}
 */

void FileDescriptor::close() {
  if (fd == -1) return;
  if (::close(fd) == -1) { with_errno() << "Failed to close file descriptor: " << fd << std::endl; }
  fd = -1;
}

FileDescriptor::~FileDescriptor() {
  close();
}

FileDescriptor FileDescriptor::duplicate() const {
  // TODO: Check errors from system calls
  return FileDescriptor{dup(fd)};
}

FileDescriptor FileDescriptor::duplicate(FileDescriptor&& new_fd) const {
  // TODO: Check errors from system calls
  new_fd.fd = dup2(fd, new_fd.fd);
  return std::move(new_fd);
}
