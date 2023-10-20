#include <gtest/gtest.h>
#include "../source/dlist.h"

TEST(DoubleLinkedList, empty_list) {
	// Fully empty double linked list

	gush::dlist<int> list{};

	ASSERT_EQ(0, list.size());
	ASSERT_FALSE(list.pop_back());
	ASSERT_FALSE(list.pop_front());
	ASSERT_EQ(list.begin(), list.end());
}

TEST(DoubleLinkedList, push_pop) {
	// Remove and push elements

	gush::dlist<int> l{};

	l.push_back(1);
	l.push_front(2);
	l.push_back(3);
	l.push_back(4);

	ASSERT_EQ(4, l.size());
	ASSERT_EQ(2, l.pop_front());
	ASSERT_EQ(1, l.pop_front());
	ASSERT_EQ(3, l.pop_front());
	ASSERT_EQ(4, l.pop_back());
}

TEST(DoubleLinkedList, iterators) {
	// Iterators are working correctly
	
	gush::dlist<int> l{};
	for (int i = 0; i < 100; i++) {
		if (i % 2 == 0) l.push_front(1);
		else l.push_back(1);
	}

	auto iterator = l.begin();
	size_t sum = 0;
	while (iterator != l.end()) {
		sum += *iterator;
		iterator++;
	}

	ASSERT_EQ(100, sum);
	ASSERT_EQ(100, l.size());
}

