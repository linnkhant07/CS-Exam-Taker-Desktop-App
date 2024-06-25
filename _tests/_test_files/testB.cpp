#include "gtest/gtest.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include "../../includes/poly/poly.h"
#include "../../includes/array_functions/array_functions.h"
// #include "../../includes/poly/poly_student.cpp"
using namespace std;

bool test_term_operators(bool debug = false)
{
    // test-error
    //  also test for CTORs
    Term t1(3.0, 2);
    Term t2(4.0, 2);

    Term t3(0, 2);
    t3 = t1 + t2;
    if (!compare_double(t3._coef, 7.0))
    {
        cout << "Term operator + not working\n";
        return false;
    }

    t3 = t1 - t2;
    if (!compare_double(t3._coef, -1.0))
    {
        cout << "Term operator - not working\n";
        return false;
    }

    t3 = t1 * t2;
    if (!compare_double(t3._coef, 12.0))
    {
        cout << "Term operator * not working\n";
        return false;
    }

    t3 = t1 / t2;
    if (!compare_double(t3._coef, 0.75))
    {
        cout << "Term operator / not working\n";
        return false;
    }

    t3 = -t1;
    if (!compare_double(t3._coef, -3.0))
    {
        cout << "Term unary operator - not working\n";
        return false;
    }

    if (!(t3 != t2))
    {
        cout << "Term operator != not working\n";
        return false;
    }

    t3 = t2;
    if (!(t3 == t2))
    {
        cout << "Term operator == not working\n";
        return false;
    }

    if (debug)
    {
        cout << "t1: " << t1 << endl;
        cout << "t2: " << t2 << endl;
        cout << "t1 + t2: " << t1 + t2 << endl;
        cout << "t1 - t2: " << t1 - t2 << endl;
        cout << "t1 * t2: " << t1 * t2 << endl;
        cout << "t1 / t2: " << t1 / t2 << endl;
        cout << "t3: " << t3 << endl;

        Term t4(3.0, 2);
        Term t5(3.0, 2);
        cout << "t4 - t5 = " << t4 - t5 << endl;
    }

    return true;
}

bool test_remainder(bool debug = false)
{
    double coefs1[] = {4.0};
    double coefs2[] = {2.0};

    Poly p(coefs1, 0);
    Poly q(coefs2, 0);
    Poly r = p % q;

    double coefs3[] = {0.0};
    Poly correct(coefs3, 0);

    if (r != correct)
    {
        cout << "r should be " << correct << " but it is instead " << r << endl;
        return false;
    }

    return true;
}

TEST(TEST_STUB, TestTermOperators)
{

    EXPECT_EQ(1, test_term_operators(false));
}

TEST(TEST_STUB, TestRemainder)
{

    EXPECT_EQ(1, test_remainder(false));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "\n\n----------running testB.cpp---------\n\n"
              << std::endl;
    return RUN_ALL_TESTS();
}
