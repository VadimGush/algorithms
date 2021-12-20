#pragma once
#include <optional>

namespace gush {
/**
 * Small wrapper for file descriptors. Makes sure that those file descriptors
 * are not copied across source code (so we can avoid calling close() twice) and
 * automatically closes current file descriptor when it's out of scope.
 */
  struct FileDescriptor {

    /**
     * Creates a new file descriptor from the raw file descriptor.
     */
    explicit FileDescriptor(int);

    /**
     * Duplicates other file descriptor using dup() system call
     * @param other  - other file desriptor
     */
    FileDescriptor(const FileDescriptor& other);

    /**
     * Closes current file descriptor and
     * duplicates other file descriptor using dup() system call
     * @param other  - other file descriptor.
     */
    FileDescriptor& operator=(const FileDescriptor& other);

    /**
     * Takes file descriptor from other file descriptor.
     * @param other - other file descriptor
     */
    FileDescriptor(FileDescriptor&& other) noexcept;

    /**
     * Closes current file descriptor and
     * takes file descriptor from other file descriptor
     * @param other - other file descriptor
     */
    FileDescriptor& operator=(FileDescriptor&& other) noexcept;

    /**
     * Calls fcntl() function to retrieve file status flags
     * @return file status flags
     */
    [[nodiscard]] int get_flags() const;

    /**
     * @return true if file descriptor is not equal to -1
     */
    [[nodiscard]] bool is_valid() const;

    /**
     * @return true if file descriptor is equal to -1
     */
    [[nodiscard]] bool is_invalid() const;

    /**
     * Duplicates current file descriptor.
     * @return new file descriptor
     */
    [[nodiscard]] std::optional<FileDescriptor> duplicate() const;

    /**
     * Duplicates current file descriptor and assigns it specified file descriptor.
     * (same as calling dup2(this.fd, new_fd.fd))
     *
     * @param new_fd - file descriptor that will be assigned to the duplicate of the current file descriptor
     * @return new file descriptor
     */
    std::optional<FileDescriptor> duplicate(FileDescriptor&& new_fd) const;

    /**
     * Closes file descriptor.
     * @return true if successful, otherwise false
     */
    bool close();

    /**
     * Calls close() to close this file descriptor
     */
    ~FileDescriptor();

    int fd;
  };
}
