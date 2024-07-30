#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/vector/vector_class.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug)
  {
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_v2(bool debug = false)
{
  char op[5] = {'a', 'b', 'c', 'd', 'e'};
  Vector<char> testing(op, 5);
  if (debug)
    cout << testing;
  testing = testing;
  if (debug)
    cout << testing;
  if (debug)
    cout << "If statement for = operator working properly\n";
  for (int i = 0; i < 10; i++)
  {
    testing += 102 + i;
    if (debug)
      cout << testing;
  }
  if (testing.at(14) != 'o')
  {
    cout << "Expected o at 15, but found " << testing.at(15) << "\n";
    return false;
  }
  if (debug)
    cout << "appended elements at the end of the vector, succesfully using +=\n";
  return true;
}

bool test_erase(bool debug = false)
{
  int c[10] = {5, 4, 3, 2, 1, 5, 6, 7, 9, 0};
  Vector<int> test(c, 10);
  if (debug)
    cout << test;
  test.erase(3);
  if (debug)
    cout << test;
  if (test[3] != 1)
  {
    cout << "Expected 1 at pos 3, but found " << test[3];
    return false;
  }
  test.erase(5);
  if (debug)
    cout << test;
  if (test[5] != 7)
  {
    cout << "Expected 7 at pos 5, but found " << test[5];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 4)
  {
    cout << "Expected 4 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 3)
  {
    cout << "Expected 3 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 1)
  {
    cout << "Expected 1 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 5)
  {
    cout << "Expected 5 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 7)
  {
    cout << "Expected 7 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 9)
  {
    cout << "Expected 9 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test[0] != 0)
  {
    cout << "Expected 0 at pos 0, but found " << test[0];
    return false;
  }
  test.erase(0);
  if (debug)
    cout << test;
  if (test.size() != 0)
  {
    cout << test.size() << "\n";
    return false;
  }

  return true;
}

TEST(VECTORIAL_TEST, TestVec2)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);
  EXPECT_EQ(1, test_v2(false));
}

TEST(FIXINGTEST, TestErase)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);
  EXPECT_EQ(1, test_erase(true));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
