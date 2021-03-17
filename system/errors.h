#pragma once

void errorMessage(const char* format, ...);

#ifdef __GNUC__
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char* format, ...) NORETURN;

void err_exit(const char* format, ...) NORETURN;

void errExitEN(int errnum, const char* format, ...) NORETURN;

void fatal(const char* format, ...) NORETURN;

void usageErr(const char* format, ...) NORETURN;

void cmdLineError(const char* format, ...) NORETURN;

// ===

void errMsg(const char* format, ...);

void errExit(const char* format, ...);

void err_exit(const char* format, ...);

void errExitEN(int errnum, const char* format, ...);
