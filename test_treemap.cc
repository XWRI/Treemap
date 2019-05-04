#include <gtest/gtest.h>
#include <string>
#include "treemap.h"

TEST(Treemap, Empty) {
  Treemap<int, int> map;

  /* Should be fully empty */
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.Get(42), std::exception);
}

TEST(Treemap, GetOneKey) {
  Treemap<int, char> map;

  /* Test Get value from key */
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(map.MinKey(), 23);
  EXPECT_EQ(map.MaxKey(), 42);
  EXPECT_EQ(map.Get(23), 'A');
}

TEST(Treemap, GetFourKey) {
  Treemap<int, char> map;

  /* Test Get values from keys */
  map.Insert(55, 'C');
  map.Insert(10, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 4);
  EXPECT_EQ(map.MinKey(), 10);
  EXPECT_EQ(map.MaxKey(), 74);
  EXPECT_EQ(map.Get(55), 'C');
  EXPECT_EQ(map.Get(10), 'D');
  EXPECT_EQ(map.Get(74), 'E');
  EXPECT_EQ(map.Get(56), 'F');
}

TEST(Treemap, GetException) {
  Treemap<int, char> map;

  /* Test in valid key */
  map.Insert(23, 'A');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 1);
  EXPECT_THROW(map.Get(10), std::exception);
}


TEST(Treemap, ContainsKey) {
  Treemap<int, char> map;

  /* Test find keys */
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  map.Insert(35, 'C');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(map.ContainsKey(23), true);
  EXPECT_EQ(map.ContainsKey(20), false);
  EXPECT_EQ(map.ContainsKey(35), true);
  EXPECT_EQ(map.ContainsKey(42), true);
}

TEST(Treemap, ContainsValue) {
  Treemap<int, char> map;

  /* Test find values */
  map.Insert(23, 'A');
  map.Insert(35, 'B');
  map.Insert(42, 'C');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(map.ContainsValue('B'), true);
  EXPECT_EQ(map.ContainsValue('A'), true);
  EXPECT_EQ(map.ContainsValue('C'), true);
  EXPECT_EQ(map.ContainsValue('D'), false);
}

TEST(Treemap, InsertOneKey) {
  Treemap<int, char> map;

  /* Test insertion */
  map.Insert(60, 'A');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(map.MinKey(), 60);
  EXPECT_EQ(map.MaxKey(), 60);
  EXPECT_EQ(map.Get(60), 'A');
}

TEST(Treemap, InsertMultipleKey) {
  Treemap<int, char> map;

  /* Test some insertions */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(10, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 10);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_EQ(map.Get(74), 'E');
}

TEST(Treemap, InsertKeyException) {
  Treemap<int, char> map;

  /* Test duplicate insertions */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(10, 'D');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 4);
  EXPECT_EQ(map.MinKey(), 10);
  EXPECT_EQ(map.MaxKey(), 60);
  EXPECT_EQ(map.Get(60), 'A');
  EXPECT_THROW(map.Insert(10, 'D'), std::exception);
  EXPECT_THROW(map.Insert(60, 'A'), std::exception);
  EXPECT_THROW(map.Insert(42, 'B'), std::exception);
}

TEST(Treemap, RemoveOneKey) {
  Treemap<int, char> map;

  /* Test removal */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(10, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 10);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_EQ(map.Get(74), 'E');
  map.Remove(90);
  EXPECT_EQ(map.MaxKey(), 88);
  EXPECT_EQ(map.Size(), 7);
  EXPECT_EQ(map.MinKey(), 10);
}

TEST(Treemap, RemoveMultipleKey) {
  Treemap<int, char> map;

  /* Test some removals */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(10, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 10);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_EQ(map.Get(74), 'E');
  map.Remove(90);
  map.Remove(88);
  map.Remove(10);
  EXPECT_EQ(map.MinKey(), 42);
  EXPECT_EQ(map.MaxKey(), 74);
  EXPECT_EQ(map.Size(), 5);
}

TEST(Treemap, RemoveException) {
  Treemap<int, char> map;

  /* Test removing from an empty tree */
  map.Insert(60, 'A');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 1);
  map.Remove(60);
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.Remove(42), std::exception);
  EXPECT_THROW(map.Remove(60), std::exception);
}

TEST(Treemap, OneCeilKey) {
  Treemap<int, char> map;

  /* Test finding the ceilkey */
  map.Insert(60, 'A');
  map.Insert(30, 'B');
  map.Insert(55, 'C');
  map.Insert(35, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.CeilKey(89), 90);
}

TEST(Treemap, CeilKeyEmptyException) {
  Treemap<int, char> map;

  /* Test finding the ceilkey when the tree is empty */
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.CeilKey(60), std::exception);
}

TEST(Treemap, MultipleCeilKey) {
  Treemap<int, char> map;

  /* Test finding some ceilkeys */
  map.Insert(60, 'A');
  map.Insert(30, 'B');
  map.Insert(55, 'C');
  map.Insert(35, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 30);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_EQ(map.CeilKey(74), 74);
  EXPECT_EQ(map.CeilKey(89), 90);
  EXPECT_EQ(map.CeilKey(57), 60);
  EXPECT_EQ(map.CeilKey(34), 35);
  EXPECT_EQ(map.CeilKey(65), 74);
  EXPECT_EQ(map.CeilKey(54), 55);
  EXPECT_EQ(map.CeilKey(25), 30);
}


TEST(Treemap, CeilKeyOutOfRangeException) {
  Treemap<int, char> map;

  /* Test key out of range */
  map.Insert(60, 'A');
  map.Insert(30, 'B');
  map.Insert(55, 'C');
  map.Insert(35, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 30);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_THROW(map.CeilKey(100), std::exception);
  EXPECT_THROW(map.CeilKey(95), std::exception);
}

TEST(Treemap, OneFloorKey) {
  Treemap<int, char> map;

  /* Test finding the floorkey */
  map.Insert(60, 'A');
  map.Insert(30, 'B');
  map.Insert(55, 'C');
  map.Insert(35, 'D');
  map.Insert(74, 'E');
  map.Insert(56, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.FloorKey(89), 88);
}

TEST(Treemap, FloorKeyEmptyException) {
  Treemap<int, char> map;

  /* Test finding the floorkey when the tree is empty */
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.FloorKey(60), std::exception);
}

TEST(Treemap, FloorKey) {
  Treemap<int, char> map;

  /* Test finding the floorkeys */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(65, 'D');
  map.Insert(74, 'E');
  map.Insert(57, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 42);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_EQ(map.FloorKey(74), 74);
  EXPECT_EQ(map.FloorKey(66), 65);
  EXPECT_EQ(map.FloorKey(56), 55);
  EXPECT_EQ(map.FloorKey(58), 57);
}

TEST(Treemap, FloorKeyOutOfRangeException) {
  Treemap<int, char> map;

  /* Test key out of range */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(65, 'D');
  map.Insert(74, 'E');
  map.Insert(57, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 8);
  EXPECT_EQ(map.MinKey(), 42);
  EXPECT_EQ(map.MaxKey(), 90);
  EXPECT_THROW(map.FloorKey(20), std::exception);
  EXPECT_THROW(map.FloorKey(30), std::exception);
}

TEST(Treemap, MinKey) {
  Treemap<int, char> map;

  /* Test minimum key */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(65, 'D');
  map.Insert(74, 'E');
  map.Insert(57, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  map.Insert(100, 'I');
  map.Insert(67, 'J');
  map.Insert(121, 'K');
  map.Insert(32, 'L');
  map.Insert(26, 'M');
  map.Insert(15, 'N');
  map.Insert(102, 'O');
  map.Insert(40, 'P');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 16);
  EXPECT_EQ(map.MinKey(), 15);
}

TEST(Treemap, MaxKey) {
  Treemap<int, char> map;

  /* Test maximum key */
  map.Insert(60, 'A');
  map.Insert(42, 'B');
  map.Insert(55, 'C');
  map.Insert(65, 'D');
  map.Insert(74, 'E');
  map.Insert(57, 'F');
  map.Insert(90, 'G');
  map.Insert(88, 'H');
  map.Insert(100, 'I');
  map.Insert(67, 'J');
  map.Insert(121, 'K');
  map.Insert(32, 'L');
  map.Insert(26, 'M');
  map.Insert(15, 'N');
  map.Insert(102, 'O');
  map.Insert(40, 'P');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 16);
  EXPECT_EQ(map.MaxKey(), 121);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
