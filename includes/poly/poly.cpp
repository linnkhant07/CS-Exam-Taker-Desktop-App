#include <iostream>
#include <iomanip>
#include <math.h>
#include "poly.h"
#include "../array_functions/array_functions.h"

using namespace std;

bool compare_double(double x, double y, double epsilon)
{
    if (fabs(x - y) < epsilon)
        return true; // they are same
    return false;    // they are not same
}

Poly::Poly() : _order(0)
{
    // size is always _order + 1
    int size = _order + 1;
    _coefs = allocate<double>(size);
    *_coefs = 0.0;
}
Poly::Poly(double *coefs, int order) : _order(order)
{
    // size is always _order + 1
    int size = _order + 1;
    _coefs = allocate<double>(size);
    copy_array(_coefs, coefs, size);

    // in case leading coefs are 0.0s
    fix_order();
}

// the BIG 3
Poly::Poly(const Poly &other) : _order(other._order)
{
    // size is always _order + 1
    int size = _order + 1;
    _coefs = allocate<double>(size);
    copy_array(_coefs, other._coefs, size);

    // in case leading coefs are 0.0s
    fix_order();
}

Poly &Poly::operator=(const Poly &rhs)
{
    if (this != &rhs)
    {
        // delete the array in the lhs first
        delete[] _coefs;
        _order = rhs._order;

        int size = _order + 1;
        _coefs = allocate<double>(_order + 1);
        copy_array(_coefs, rhs._coefs, size);
    }

    return *this;
}

Poly::~Poly()
{
    delete[] _coefs;
}

bool operator==(const Poly &lhs, const Poly &rhs)
{
    if (lhs._order != rhs._order)
        return false;

    // lhs._order is the same as rhs
    for (int i = 0; i < lhs._order + 1; i++)
    {
        if (!compare_double(lhs[i]._coef, rhs[i]._coef))
            return false;
    }
    return true;
}

bool operator!=(const Poly &lhs, const Poly &rhs)
{
    return !(lhs == rhs);
}

bool operator>(const Poly &lhs, const Poly &rhs)
{
    if (lhs._order > rhs._order)
        return true;

    else if (lhs._order < rhs._order)
        return false;

    // if orders are the same
    for (int i = rhs._order; i >= 0; i--)
    {
        // start from the biggest exp
        if (lhs[i] > rhs[i])
            return true;

        else if (lhs[i] < rhs[i])
            return false;

        // continues looping if coefs are the same
    }

    return false;
}
bool operator<(const Poly &lhs, const Poly &rhs)
{
    return !(lhs > rhs);
}

Term Poly::operator[](int order) const
{
    // index order
    double *walker = _coefs + order;
    // exponent is order;
    Term t(*walker, order);
    return t;
}

Poly operator+(const Poly &lhs, const Term &t)
{

    Poly result(lhs);                                        // sum poly
    int order = (lhs._order > t._exp) ? lhs._order : t._exp; // bigger exp

    // reallocate _coefs if new order is larger
    if (order > result._order)
    {
        int size = order + 1;              // new order
        int curr_size = result._order + 1; // old order
        result._coefs = reallocate(result._coefs, curr_size, size);
        result._order = order; // new order
    }

    // add coefficients in that index
    double *walker = result._coefs + t._exp;
    *walker += t._coef;

    return result;
}

Poly operator+(const Poly &lhs, const Poly &rhs)
{
    Poly temp(lhs);
    // add every term from the rhs poly
    for (int i = 0; i < rhs._order + 1; i++)
    {
        temp = temp + rhs[i];
    }

    // get rid of the biggest coefs with zeroes
    temp.fix_order();
    return temp;
}

Poly operator-(const Poly &p)
{
    int size = p._order + 1;
    Poly result(p);

    // negate all indexes
    for (int i = 0; i < size; i++)
    {
        double *walker = result._coefs + i;
        *walker *= -1;
    }

    return result;
}

Poly operator-(const Poly &lhs, const Poly &rhs)
{
    Poly p = lhs + (-rhs);
    // get rid of the biggest coefs with zeroes

    p.fix_order();
    return p;
}

Poly operator*(const Poly &lhs, const Term &t)
{
    // create an empty poly
    Poly result;

    // find the bigger exponent out of two
    int order = lhs._order + t._exp;

    // reallocate if order is larger
    if (order > result._order)
    {
        int size = order + 1;              // new order
        int curr_size = result._order + 1; // old order of result
        result._coefs = reallocate(result._coefs, curr_size, size);
        result._order = order;
    }

    for (int i = 0; i < lhs._order + 1; i++)
    {
        // points to the resulting exp
        double *walker = result._coefs + (t._exp + i);
        *walker = lhs[i]._coef * t._coef;
    }

    return result;
}

Poly operator*(const Poly &lhs, const Poly &rhs)
{
    // order is the combination of biggest exponents
    int order = lhs._order + rhs._order;

    Poly p; // create a Poly with empty array
    // multiply lhs with all the terms from rhs
    for (int i = 0; i < rhs._order + 1; i++)
    {
        p = p + (lhs * rhs[i]);
    }
    p.fix_order();
    return p;
}

Poly operator/(const Poly &lhs, const Poly &rhs)
{
    // lhs = dividend, rhs = divisor
    Poly result; // create an empty poly

    // if dividend is 0 x0
    assert(rhs._order != 0 || rhs[0]._coef != 0);

    //  if dividend is less than divisor
    if (lhs._order < rhs._order)
        return result;

    // order exponent of the quotient
    int order = lhs._order - rhs._order;
    int size = order + 1;              // new order
    int curr_size = result._order + 1; // old order of result

    result._coefs = reallocate(result._coefs, curr_size, size);
    result._order = order;

    // dividend will keep changing, so we have to make a copy of lhs (to not change lhs)
    Poly dividend(lhs);

    // while dividend is still divisible by rhs
    while (dividend._order >= rhs._order && !(*dividend._coefs == 0 && dividend._order == 0))
    {

        int d_order = dividend._order;
        int r_order = rhs._order;

        // point to the exp index of quotient
        int exp_diff = d_order - r_order;
        double ratio = dividend[d_order]._coef / rhs[r_order]._coef;

        double *walker = result._coefs + exp_diff;
        *walker = ratio;

        Term q(ratio, exp_diff);

        // the new dividend
        dividend = dividend - (rhs * q);
    } // continue dividing the dividend

    result.fix_order();
    return result;
}

ostream &operator<<(ostream &outs, const Poly &p)
{
    outs << "[ ";
    for (int i = p._order; i >= 0; i--)
    {
        outs << fixed << setprecision(1) << p[i];
    }
    outs << "] ";
    return outs;
}

istream &operator>>(istream &ins, Poly &p)
{
    // create an empty poly and assign to p
    Poly temp_poly;
    p = temp_poly;

    // to extract from istream
    double coefficient;
    int exponent;

    char c;

    // while there is still input
    // c takes out 'x'
    while (ins >> coefficient >> c >> exponent)
    {
        // create a term and add it to p
        Term t(coefficient, exponent);
        p = p + t;

        // break if the next character is newline
        if (ins.peek() == '\n')
        {
            break;
        }
    }

    return ins;
}

double *Poly::get_coefs() const
{
    return _coefs;
}

void Poly::set_order(int new_order)
{

    _order = new_order;
} // Not used!

void Poly::fix_order()
{
    // start from the highest order
    double *ptr = _coefs + _order;
    // not i >= 0 because we want to leave the last index
    // to avoid order being negative
    for (int i = _order; i > 0; i--, ptr--)
    {
        if (*ptr == 0)
            _order--;
        // once the coeff is not zero, no need to change order
        else
            break;
    }
} // get rid of highest terms with zero coefs
