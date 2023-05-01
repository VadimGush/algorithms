//
// Created by Vadim Gush on 01.05.2023.
//
#include <gtest/gtest.h>
#include "../src/vector.h"

TEST(VectorTest, empty_vector) {
    gush::vector<int> vec{};

    const auto last_element = vec.pop_back();
    ASSERT_FALSE(last_element);
    ASSERT_EQ(0, vec.size());
    ASSERT_EQ(vec.begin(), vec.end());
}

TEST(VectoTest, initializer_list) {
    gush::vector<int> vec{1, 2, 3, 4};

    ASSERT_EQ(4, vec.size());
    ASSERT_EQ(1, vec.get(0));
    ASSERT_EQ(2, vec.get(1));
    ASSERT_EQ(3, vec.get(2));
    ASSERT_EQ(4, vec.get(3));
}

TEST(VectorTest, push_back) {
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
    gush::vector<int> vec{};
    vec.insert(0, 2);
    vec.insert(0, 1);
    vec.insert(0, 0);
    vec.remove(1);

    ASSERT_EQ(2, vec.size());
    ASSERT_EQ(0, vec.get(0));
    ASSERT_EQ(2, vec.get(1));
}

