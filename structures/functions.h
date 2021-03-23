#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Prints content of the array
 */
void array_print(const int[], size_t);

/**
 * Checks if two arrays are equal
 * @return true if equal otherwise false
 */
bool array_equals(const int[], const int[], size_t);

/**
 * Returns max element
 */
int max(int, int);

/**
 * Calculates factorial of given numbers
 * Time complexity: O(N)
 */
int factorial(int);

int great_common_divisor(int, int);

float float_pow(float, int);

int int_pow(int, int);

/**
 * Swaps two values
 */
void swap(int*, int*);

/**
 * The slowest implementation of algorithm for calculating fib numbers
 * Time complexity: O(fib(n))
 */
int slow_fib(int);

/**
 * Fast algorithm for calculating fib numbers
 * Time complexity: O(N)
 * Space complexity: O(N)
 */
int fast_fib(int);

/**
 * Compares two strings
 */
bool compare_str(char*, char*);

/**
 * Compares two arrays of data
 */
bool data_compare(void*, void*, size_t);

