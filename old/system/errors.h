#pragma once

/*
 * That means that every function with such attribute
 * doesn't return anything (like exit() function) and compiler
 * can optimize calls of those functions
 */
#ifdef __GNUC__
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/*
 * Prints error message to standart error, depending on errno value
 */
void err_msg(const char* format, ...);

/**
 * Prints error message depending on errno value and terminates a program
 */
void err_msg_exit(const char* format, ...) NORETURN;

/**
 * Prints error message depending on provided errnum value and terminates a program
 */
void err_msg_num_exit(int errnum, const char* format, ...) NORETURN;

/**
 * Prints error message without flashing standart output before printing a new message.
 * Also doesn't flush before terminating
 *
 * Useful for multithreaded applications (uses _exit(2) syscall)
 */
void err_exit(const char* format, ...) NORETURN;

/**
 * Prints error message and terminates a program
 */
void fatal(const char* format, ...) NORETURN;

/**
 * Prints usage error message and terminates a program
 */
void usage_err(const char* format, ...) NORETURN;

/**
 * Same as usage_err() but for command-line arguments
 */
void cmd_line_err(const char* format, ...) NORETURN;

