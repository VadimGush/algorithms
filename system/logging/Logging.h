#pragma once
#include <iostream>

/**
 * Prints "ERROR: " to the standard error output
 * @return reference to prepared output stream
 */
std::ostream& error();

/**
 * Prints error from errno global variable to the standard error output
 * @return reference to prepared output stream
 */
std::ostream& with_errno();
