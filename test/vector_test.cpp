#include <gtest/gtest.h>
#include "../source/vector.h"

TEST(VectorTest, empty_vector) {
	// Empty vector has no elements and size is 0
    gush::vector<int> vec{};

    const auto last_element = vec.pop_back();
    ASSERT_FALSE(last_element);
    ASSERT_EQ(0, vec.size());
    ASSERT_EQ(vec.begin(), vec.end());
}

TEST(VectoTest, initializer_list) {
	// Constructor with initializer list works correctly
    gush::vector<int> vec{1, 2, 3, 4};

    ASSERT_EQ(4, vec.size());
    ASSERT_EQ(1, vec.get(0));
    ASSERT_EQ(2, vec.get(1));
    ASSERT_EQ(3, vec.get(2));
    ASSERT_EQ(4, vec.get(3));
}

TEST(VectorTest, push_back) {
	// Push back inserts elements correctly
    gush::vector<int> vec{};
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    ASSERT_EQ(3, vec.size());
    ASSERT_EQ(1, vec.get(0));
    ASSERT_EQ(2, vec.get(1));
    ASSERT_EQ(3, vec.get(2));
}

TEST(VectorTest, insert_remove) {
	// Remove does indeed work
    gush::vector<int> vec{};
    vec.insert(0, 2);
    vec.insert(0, 1);
    vec.insert(0, 0);
    vec.remove(1);

    ASSERT_EQ(2, vec.size());
    ASSERT_EQ(0, vec.get(0));
    ASSERT_EQ(2, vec.get(1));
}

TEST(VectorTest, insert_remove_empty) {
	// We can remove all elements and then get the empty container
	// without any negative size
	
	gush::vector<int> vec{};
	vec.insert(0, 1);
	vec.insert(0, 2);
	vec.insert(0, 3);
	vec.remove(0);
	vec.remove(0);
	vec.remove(0);
	vec.remove(0);

	ASSERT_EQ(0, vec.size());
}

TEST(VectorTest, resize_container) {
	// Vector does resize when there are too many elements
	
	gush::vector<int> vec{};

	for (int i = 0; i < 1000; i++) {
		vec.push_back(i);
	}

	for (int i = 0; i < 1000; i++) {
		ASSERT_EQ(i, vec[i]);
	}
}

TEST(VectorTest, iterators) {
	gush::vector<int> vec{};
	for (int i = 0; i < 1000; i++) {
		vec.push_back(i);
	}

	auto iterator = vec.begin();
	size_t id = 0; 
	while (iterator != vec.end()) {
		ASSERT_EQ(vec[id], *iterator);

		id += 1;
		iterator++;
	}
}

