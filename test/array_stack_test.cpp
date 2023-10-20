#include <gtest/gtest.h>
#include "../source/array_stack.h"

TEST(ArrayStack, empty_array_stack) {
	// Empty stack has no elements

	gush::array_stack<int> stack{};

	ASSERT_EQ(0, stack.size());
	ASSERT_FALSE(stack.pop());
}

TEST(ArrayStack, push_pop) {
	// stack inserts and removes elements
	// correctly

	gush::array_stack<int> stack{};
	stack.push(1);
	stack.push(2);
	stack.push(3);

	ASSERT_EQ(3, stack.size());
	ASSERT_EQ(3, stack.pop());
	ASSERT_EQ(2, stack.pop());
	ASSERT_EQ(1, stack.pop());
}

TEST(ArrayStack, iterators) {
	// Iterators are working correctly
	
	gush::array_stack<int> stack{};

	for (int i = 0; i < 100; i++) {
		stack.push(1);
	}
	for (int i = 0; i < 20; i++) {
		stack.pop();
	}

	auto iterator = stack.begin();
	size_t sum = 0;
	while (iterator != stack.end()) {
		sum += *iterator;
		iterator++;
	}

	ASSERT_EQ(80, sum);
	ASSERT_EQ(80, stack.size());
}
