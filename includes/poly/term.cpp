#include <iostream>
#include "term.h"
#include "assert.h"
#include <math.h>

using namespace std;

// compare doubles function
bool d_is_equal(double x, double y, double epsilon = 0.001f)
{
    if (fabs(x - y) < epsilon)
        return true; // they are same
    return false;    // they are not same
}

Term::Term(double coef, int exp) : _coef(coef), _exp(exp)
{
}

bool operator==(const Term &lhs, const Term &rhs)
{
    return d_is_equal(lhs._coef, rhs._coef);
}
bool operator!=(const Term &lhs, const Term &rhs)
{
    return !d_is_equal(lhs._coef, rhs._coef);
}

bool operator>(const Term &lhs, const Term &rhs)
{
    if (lhs._exp > rhs._exp)
        return true;

    if (lhs._exp == rhs._exp && lhs._coef > rhs._coef)
        return true;

    return false;
}
bool operator<(const Term &lhs, const Term &rhs)
{
    if (lhs._exp < rhs._exp)
        return true;

    if (lhs._exp == rhs._exp && lhs._coef < rhs._coef)
        return true;

    return false;
}

Term operator+(const Term &lhs, const Term &rhs)
{
    // end if exponents are not equal
    assert(lhs._exp == rhs._exp);

    Term temp(0, lhs._exp);
    temp._coef = lhs._coef + rhs._coef;

    return temp;
}

Term operator-(const Term &t)
{
    // negative the coef
    Term temp(0, t._exp);
    temp._coef = t._coef * -1;

    return temp;
}

Term operator-(const Term &lhs, const Term &rhs)
{
    return lhs + (-rhs);
}

Term operator*(const Term &lhs, const Term &rhs)
{

    // powers of the same base combine
    Term temp(0, lhs._exp + rhs._exp);
    temp._coef = lhs._coef * rhs._coef;

    return temp;
}

// used in Poly division operator
Term operator/(const Term &lhs, const Term &rhs)
{

    // powers of the same base subtract
    Term temp(0, lhs._exp - rhs._exp);
    temp._coef = lhs._coef / rhs._coef;

    return temp;
}

ostream &operator<<(ostream &outs, const Term &t)
{
    // don't print if the coefficient is empty
    if (t._coef == 0)
        return outs;

    outs << ((t._coef > 0) ? "+" : "");

    if (t._exp == 1)
        outs << t._coef << "X ";
    else if (t._exp == 0)
        outs << t._coef << " ";
    else
        outs << t._coef << "X^" << t._exp << " ";

    return outs;
}
