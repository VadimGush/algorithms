# Single Unix Specification: Version 3

## Header files
List of header files that are defined in SUSv3 with list of some defined functions and constants.

| Header file | Description | Functions and constants (example) |
| ----------- | ----------- | ----------------------- |
| `unistd.h`       | standard symbolic constants and types | `close()` `dub()` `fdatasync()` `fsync()` `lseek()` `getpid()` `read()` `write()` `sysconf()` `pathconf()` |
| `fcntl.h`        | file control options | `open()` `fcntl()` |
| `time.h`         | time types | `clock()` `CLOCKS_PER_SEC` |
| `pwd.h`          | password structure | `getpwnam()` `getpwuid()` `struct passwd` |
| `stdio.h`        | standard buffered input/output | `printf()` `fprintf()` `fflush()` `setvbuf()` |
| `sys/times.h`    | file access and modification times structure | `times()` |
| `sys/utsname.h`  | system name structure | `uname()` |
| `sys/statvfs.h`  | VFS File System information structure | `statvfs()` |
