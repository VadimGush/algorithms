#include "Operations.h"
#include <iostream>

// === POSIX Standard ===
/*
 * Definition of file descriptors (stdout, stdin, etc)
 */
#include <unistd.h>
/*
 * Definition for different file modes/permissions
 */
#include <sys/stat.h>
/*
 * File control operations:
 * open(), read(), write(), close() and etc.
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

ostream& error() { return cerr << "ERROR: "; }

ostream& with_errno() {
  switch (errno) {
    case EACCES: error() << "Permission denied"; break;
    case EISDIR: error() << "Specified file is a directory"; break;
    case EMFILE: error() << "Process resource limit on the number of opened file descriptors has been reached"; break;
    case ENFILE: error() << "The system-wide limit on the number of open files has been reached"; break;
    case ENOENT: error() << "The specified file doesn't exists"; break;
    case ETXTBSY: error() << "The specified file is an executable which is currently in-use"; break;
    default: return error();
  }
  cerr << endl << "Message: ";
  return cerr;
}

void copy(const string& from, const string& to) {
  char buffer[BUFFER_SIZE];
  auto fd1 = open(from.c_str(), O_RDONLY);
  if (fd1 == -1) { with_errno() <<  "Failed to open the file '" << to << "'" << endl; return; }

  auto fd2 = open(to.c_str(),
                  // file mode
                  O_WRONLY | O_CREAT | O_TRUNC,
                  // file permissions
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (fd2 == -1) { with_errno() << "Failed to open the file '" << to << "'" << endl; return; }

  ssize_t count;
  ssize_t sum = 0;
  while ((count = read(fd1, buffer, BUFFER_SIZE)) > 0) {
    sum += count;
    auto w_count = write(fd2, buffer, count);
    if (w_count == -1) { error() <<  "Failed to write data to '" << to << "' file." << endl; return; }
  }
  cout << "copy(): Copied " << sum << " bytes" << endl;

  auto status = close(fd1);
  if (status == -1) { error() << "Failed to close '" << from << "' file." << endl; }
  status = close(fd2);
  if (status == -1) { error() << "Failed to close '" << to << "' file." << endl; }
}
