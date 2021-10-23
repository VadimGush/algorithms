#pragma once
#include <string>

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
 */
void copy(const std::string& from, off_t from_pos, const std::string& to);