#include "Logging.h"
#include <unistd.h>
#include <cmath>
#include <algorithm>
using namespace std;

const OutStream std_out{};
const ErrStream std_err{};
const char* ln = "\n";

static void write_string(const int fd, const char* const text){
  size_t size = 0;
  while (text[size] != '\0') {
    size++;
  }
  write(fd, text, size);
}

static void write_number(const int fd, const int value) {
  const auto v = abs(value);
  const auto digits = max((unsigned int)floor(log10(v) + 1), 1u);
  char buffer[32]{'-'};
  constexpr int s = '0';
  for (int i = (int)digits - 1; i >= 0; i--) {
    // we calculate pow twice which is not quite nice
    buffer[(digits) - i] = (char)(s + ((v % (int)pow(10, i + 1)) / (int)(pow(10, i))));
  }
  const bool n = value < 0;
  write(fd, buffer + !n, digits + n);
}

const OutStream& OutStream::operator<<(const char *message) const {
  write_string(STDOUT_FILENO, message);
  return *this;
}

const OutStream& OutStream::operator<<(const int value) const {
  write_number(STDOUT_FILENO, value);
  return *this;
}

const OutStream& OutStream::operator<<(const std::string& message) const {
  return *this << message.c_str();
}

const ErrStream& ErrStream::operator<<(const char* message) const {
  write_string(STDERR_FILENO, message);
  return *this;
}

const ErrStream& ErrStream::operator<<(const int value) const {
  write_number(STDERR_FILENO, value);
  return *this;
}

const ErrStream& ErrStream::operator<<(const std::string& message) const {
  return *this << message.c_str();
}

const ErrStream& error() { return std_err << "Error: "; }

const ErrStream& with_errno() {
  switch (errno) {
    case EACCES: error() << "Permission denied"; break;
    case EISDIR: error() << "Specified file is a directory"; break;
    case EMFILE: error() << "Process resource limit on the number of opened file descriptors has been reached"; break;
    case ENFILE: error() << "The system-wide limit on the number of open files has been reached"; break;
    case ENOENT: error() << "The specified file doesn't exists"; break;
    case ETXTBSY: error() << "The specified file is an executable which is currently in-use"; break;
    case EPERM: error() << "Operation is not permitted"; break;
    case EBADF: error() << "Bad file descriptor"; break;
    case EINTR: error() << "System call was interrupted"; break;
    case EIO: error() << "I/O error occurred"; break;
    case EEXIST: error() << "File already exists"; break;
    case ENOSPC: error() << "No space left on the device"; break;
    case EDQUOT: error() << "Disk quota exceeded"; break;
    case EAGAIN: error() << "Resource is temporary unavailable or system call would block"; break;
    case EDESTADDRREQ: error() << "Destination address is required"; break;
    case EFAULT: error() << "Bad address"; break;
    default: error() << "Unrecognizable error: " << errno;
  }
  std_err << ln << "Message: ";
  return std_err;
}
