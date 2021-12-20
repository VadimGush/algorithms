#include "Operations.h"
#include "Logging.h"

// === POSIX Standard ===
/*
 * Definition of file descriptors (stdout, stdin, etc)
 * and basic functions such as close(), read(), write()
 */
#include <unistd.h>
/*
 * Definition for different file modes/permissions
 */
#include <sys/stat.h>
/*
 * readv(), writev()
 */
#include <sys/uio.h>
/*
 * File control: file modes (such as O_WRONLY, O_RDONLY), declaration of fcntl()
 * function and etc.
 */
#include <fcntl.h>
/*
 * Basic utils for sizes: size_ts and size_t
 */
#include <monetary.h>
/*
 * System error numbers (errno.h)
 */
#include <cerrno>

static constexpr size_t BUFFER_SIZE = 128 * 1024; // 128 Kb
using namespace std;

void copy(const string& from, const off_t from_pos, const string& to, const off_t to_pos) {
  auto fd1 = gush::FileDescriptor{open(from.c_str(), O_RDONLY)};
  if (fd1.is_invalid()) { with_errno() <<  "Failed to open the file '" << to << "'" << ln; return; }

  auto fd2 = gush::FileDescriptor{open(to.c_str(),
      /*
       * If we put O_SYNC status flag here, it will inform the kernel
       * to perform synchronized I/O file integrity completion (metadata will be guaranteed to be written at least
       * to the cache of hard drive). We can also use O_DSYNC which will trigger
       * synchronized I/O data integrity completion.
       */
      O_WRONLY /* access mode */ | O_CREAT | O_TRUNC | O_EXCL, // status flags
      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)};
  if (fd2.is_invalid()) { with_errno() << "Failed to open the file '" << to << "'" << ln; return; }

  lseek(fd1.fd, from_pos, SEEK_SET);
  lseek(fd2.fd, to_pos, SEEK_SET);

  char buffer[BUFFER_SIZE];
  ssize_t count;
  ssize_t processed_bytes = 0;
  ssize_t copied_bytes = 0;
  while ((count = read(fd1.fd, buffer, BUFFER_SIZE)) > 0) {
    processed_bytes += count;

    // Check if buffer contains only nulls (possibly a file hole)
    // in that case we will not perform any write and just move to the next position
    bool hole = true;
    for (size_t i = 0; i < count; i++) {
      if (buffer[i] != 0) { hole = false; break; }
    }

    if (hole) {
      lseek(fd2.fd, count, SEEK_CUR);
    } else {
      copied_bytes += count;
      auto w_count = write(fd2.fd, buffer, count);
      if (w_count == -1) { with_errno() <<  "Failed to write data to '" << to << "' file." << ln; return; }
    }
  }
}

void write_strings(const string& file, const vector<string>& strings) {
  auto tfd = gush::FileDescriptor{open(file.c_str(),
    O_CREAT | O_APPEND | O_EXCL | O_WRONLY,
    S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP)};

  if (tfd.is_invalid()) { with_errno() << "Failed to create '" << file << "' file"; return; }

  int size = (int) strings.size();
  iovec buffers[size];
  for (size_t i = 0; i < strings.size(); i++) {
    const string& str = strings[i];
    buffers[i].iov_len = str.size();
    buffers[i].iov_base = const_cast<char*>(str.c_str());
  }

  const auto bytes = writev(tfd.fd, buffers, size);
  std_out << "write_strings(): Wrote " << (int)bytes << " bytes" << ln;
}

void copy(const string& from, const string& to) {
  copy(from, 0, to, 0);
}

optional<gush::FileDescriptor> create_temporary(const string& pattern) {
  char new_pattern[pattern.size() + 1];
  for (size_t i = 0; i < pattern.size(); i++) {
    new_pattern[i] = pattern.c_str()[i];
  }
  new_pattern[pattern.size()] = '\0';

  auto fd = gush::FileDescriptor{mkstemp(new_pattern)};
  if (fd.is_invalid()) { with_errno() << "Failed to create a temporary file" << ln; return {}; }
  std_out << "Generated filename was '" << new_pattern << "'" << ln;
  return move(fd);
}