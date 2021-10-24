#include "Operations.h"
#include "types/FileDescriptor.h"
#include "logging/Logging.h"
#include <iostream>

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
 * File control contains definition of file modes
 * such as: O_WRONLY, O_RDONLY and etc.
 */
#include <fcntl.h>
/*
 * Basic types for sizes: size_ts and size_t
 */
#include <monetary.h>
/*
 * System error numbers (errno.h)
 */
#include <cerrno>

static constexpr size_t BUFFER_SIZE = 1024;
using namespace std;

void copy(const string& from, const off_t from_pos, const string& to, const off_t to_pos) {
  char buffer[BUFFER_SIZE];
  auto fd1 = FileDescriptor{open(from.c_str(), O_RDONLY)};
  if (fd1.fd == -1) { with_errno() <<  "Failed to open the file '" << to << "'" << endl; return; }

  // O_APPEND will guarantee that seek and write will happen atomically
  // but by now we're just writing from the beginning of the file
  auto fd2 = FileDescriptor{open(to.c_str(),
      // file mode
      O_WRONLY | O_CREAT | O_TRUNC,
      // file permissions
      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)};
  if (fd2.fd == -1) { with_errno() << "Failed to open the file '" << to << "'" << endl; return; }

  lseek(fd1.fd, from_pos, SEEK_SET);
  lseek(fd2.fd, to_pos, SEEK_SET);

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
      if (w_count == -1) { with_errno() <<  "Failed to write data to '" << to << "' file." << endl; return; }
    }
  }
  cout << "copy(): Processed " << processed_bytes << " bytes" << endl;
  cout << "        Copied " << copied_bytes << " bytes" << endl;
}

void copy(const string& from, const string& to) {
  copy(from, 0, to, 0);
}