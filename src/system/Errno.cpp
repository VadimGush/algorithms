#include "Errno.h"
#include <cerrno>

const char* gush::get_errno_message() {

  switch (errno) {
    case EACCES: return "Permission denied";
    case EISDIR: return "Specified file is a directory";
    case EMFILE: return "Process resource limit on the number of opened file descriptors has been reached";
    case ENFILE: return "The system-wide limit on the number of open files has been reached";
    case ENOENT: return "The specified file doesn't exists";
    case ETXTBSY: return "The specified file is an executable which is currently in-use";
    case EPERM: return "Operation is not permitted";
    case EBADF: return "Bad file descriptor";
    case EINTR: return "System call was interrupted";
    case EIO: return "I/O error occurred";
    case EEXIST: return "File already exists";
    case ENOSPC: return "No space left on the device";
    case EDQUOT: return "Disk quota exceeded";
    case EAGAIN: return "Resource is temporary unavailable or system call would block";
    case EDESTADDRREQ: return "Destination address is required";
    case EFAULT: return "Bad address";
  }

  return nullptr;
}