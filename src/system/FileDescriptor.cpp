#include "FileDescriptor.h"
#include <unistd.h>
#include <fcntl.h>
using namespace gush;

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

bool FileDescriptor::close() {
  if (fd == -1) { return true; }
  auto status = ::close(fd);
  fd = -1;
  return status != -1;
}

FileDescriptor::~FileDescriptor() {
  close();
}

std::optional<FileDescriptor> FileDescriptor::duplicate() const {
  const int new_fd = dup(fd);
  if (new_fd == -1) { return {}; }
  return FileDescriptor{ new_fd };
}

std::optional<FileDescriptor> FileDescriptor::duplicate(FileDescriptor&& new_fd) const {
  new_fd.fd = dup2(fd, new_fd.fd);
  if (new_fd.fd == -1) { return {}; }
  return std::move(new_fd);
}
