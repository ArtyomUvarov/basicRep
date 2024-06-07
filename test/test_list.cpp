
#include <gtest/gtest.h>
#include <list>

struct ListFix : public testing::Test {

  const size_t elementCount = 10;
  std::list<size_t> list; //the same list instance for all test cases
  // Per-test set-up
  void SetUp() override {
    std::cout << "SetUp" << std::endl;

    // Create list with elementCount elements
    for (size_t i = 0; i < elementCount; ++i)
      list.push_back(i);
  } 
};



TEST(List, Create) {
  std::list<int> list;
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());
}

TEST_F(ListFix, PushBack) {
   list.push_back(20);
   ASSERT_EQ(list.size(), 11);
   ASSERT_EQ(list.back(), 20);
}

TEST_F(ListFix, PopBack) {
  list.pop_back();
  ASSERT_EQ(list.size(), 9);
  ASSERT_EQ(list.back(), 8);
   
}

TEST_F(ListFix, Insert) {
  size_t i = 0;
  auto iter = list.begin();

  for (auto currIter = list.begin(); i<6; currIter++, ++i)
    iter = currIter;

  list.insert(iter,60); 
  ASSERT_EQ(list.size(), 11); //вставка произошла
  // проверяем, что элемент 60 вставился между 4 и 5.
  ASSERT_EQ(*(iter), 5); 
  ASSERT_EQ(*(--iter), 60); 
  --iter;
  ASSERT_EQ(*(iter), 4); 

}

TEST_F(ListFix, PushFront) {
  list.push_front(20);
  ASSERT_EQ(list.size(), 11);
  ASSERT_EQ(list.front(), 20);
}

TEST_F(ListFix, PopFront) {
  list.pop_front();
  ASSERT_EQ(list.size(), 9);
  ASSERT_EQ(list.front(), 1);

}

TEST_F(ListFix, Erase) {
  size_t i = 0;
  auto iter = list.begin();

  for (auto currIter = list.begin(); i < 6; currIter++, ++i)
    iter = currIter;

  auto prevIter = --iter;
  iter++;
  list.erase(iter);
  ASSERT_EQ(list.size(), 9); //удаление произошло
  // проверяем, что удалился элемент между 4 и 6.
  ASSERT_EQ(*(prevIter), 4);
  ASSERT_EQ(*(++iter), 6);
}

TEST_F(ListFix, Size) {
  ASSERT_EQ(list.size(), 10);
}

TEST_F(ListFix, Getelement) {
    size_t arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    size_t i = 0;

    for (size_t elem : list)
      ASSERT_EQ( elem, arr[i++] ); //can't understand where is failure
        
}

TEST_F(ListFix, Clear) {
  list.clear();
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}