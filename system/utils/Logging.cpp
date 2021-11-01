#include "Logging.h"
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
    default: return error();
  }
  cerr << endl << "Message: ";
  return cerr;
}
