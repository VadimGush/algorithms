#include <gtest/gtest.h>
#include "../source/array_deque.h"

TEST(ArrayDeque, empty_deque) {
	// Empty deque has no elements

	gush::array_deque<int> d{};

	ASSERT_EQ(0, d.size());
	ASSERT_FALSE(d.pop_front());
	ASSERT_FALSE(d.pop_back());
}

TEST(ArrayDeque, pop_push) {
	// Inserts both and back and front
	// as well as removal of elements 

	gush::array_deque<int> d{};

	d.push_back(1);
	d.push_back(2);
	d.push_front(0);
	d.push_front(1);
	d.push_front(2);

	ASSERT_EQ(5, d.size());
	ASSERT_EQ(2, d.pop_front());
	ASSERT_EQ(1, d.pop_front());
	ASSERT_EQ(0, d.pop_front());
	ASSERT_EQ(2, d.pop_back());
	ASSERT_EQ(1, d.pop_back());
}

TEST(ArrayDeque, iterators) {
	// Iterators should work correctly

	gush::array_deque<int> d{};

	for (int i = 0; i < 500; i++) {
		d.push_back(1);
	}
	for (int i = 0; i < 100; i++) {
		d.pop_front();
	}
	for (int i = 0; i < 200; i++) {
		d.push_front(1);
	}

	auto iter= d.begin();
	int sum = 0;
	while (iter!= d.end()) {
		sum += *iter;
		iter++;
	}

	ASSERT_EQ(600, d.size());
	ASSERT_EQ(600, sum);
}
