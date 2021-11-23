#pragma once
#include <string>

struct OutStream {
  // TODO: Add buffering
  const OutStream& operator<<(const std::string& message) const;
  const OutStream& operator<<(const char* message) const;
  const OutStream& operator<<(int value) const;
};

struct ErrStream {
  const ErrStream& operator<<(const std::string& message) const;
  const ErrStream& operator<<(const char* message) const;
  const ErrStream& operator<<(int value) const;
};

extern const ErrStream std_err;
extern const OutStream std_out;
extern const char* ln;

/**
 * Prints "ERROR: " to the standard error output
 * @return reference to prepared output stream
 */
const ErrStream& error();

/**
 * Prints error from errno global variable to the standard error output
 * @return reference to prepared output stream
 */
const ErrStream& with_errno();
