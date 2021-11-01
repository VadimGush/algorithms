#pragma once
#include <string>
#include <vector>
#include <optional>
#include "utils/FileDescriptor.h"

/**
 * The same as calling copy(from, 0, to).
 *
 * @param from - name of the file to copy from
 * @param to - name of the file to copy to
 */
void copy(const std::string& from, const std::string& to);

/**
 * Copies data from one file (from specified position) to another.
 * Any file holes will be transferred (without copying nulls) to the target file.
 *
 * @param from - name of the file to copy from
 * @param from_pos - position (in bytes) to start copy from
 * @param to - name of the file to copy to
 * @param to_pos - position (in bytes) in created file at which data is written
 */
void copy(const std::string& from, off_t from_pos, const std::string& to, off_t to_pos);

/**
 * Writes an array of strings to a single file. Write operations are performed using
 * scatter-gather I/O in one atomic operation.
 *
 * @param file - file to write content to
 * @param strings - array of strings
 */
void write_strings(const std::string& file, const std::vector<std::string>& strings);

/**
 * Creates a temporary file and returns its file descriptor. This file will be removed
 * after current process will finish execution.
 *
 * @param pattern - pattern for file name. Should end with XXXXXX
 */
std::optional<FileDescriptor> create_temporary(const std::string& pattern);
