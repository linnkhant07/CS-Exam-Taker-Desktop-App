#ifndef POLY_H
#define POLY_H

#include "term.h"

#include <iostream>
#include <vector>

using namespace std;

bool compare_double(double x, double y, double epsilon = 0.001f);

class Poly
{
public:
    Poly();
    Poly(double *coefs, int order);

    // the BIG 3
    Poly(const Poly &other);
    Poly &operator=(const Poly &rhs);
    ~Poly();

    friend bool operator==(const Poly &lhs, const Poly &rhs);
    // postcondition: returns true if lhs and rhs are equal

    friend bool operator!=(const Poly &lhs, const Poly &rhs);
    // postcondition: returns true if lhs and rhs are not equal

    friend bool operator>(const Poly &lhs, const Poly &rhs);
    // postcondition: returns true if lhs > rhs

    friend bool operator<(const Poly &lhs, const Poly &rhs);
    // postcondition: returns true if lhs < rhs

    // precondition: order is not negative
    Term operator[](int order) const;
    // postcondition: returns a term made with 'order' exp and its coefficient

    friend Poly operator+(const Poly &lhs, const Term &t);
    // postcondition: returns a sum poly

    friend Poly operator+(const Poly &lhs, const Poly &rhs);
    // postcondition: returns a sum poly

    friend Poly operator-(const Poly &p);
    // postcondition: returns a subtraction poly

    friend Poly operator-(const Poly &lhs, const Poly &rhs);
    // postcondition: returns a subtraction poly

    friend Poly operator*(const Poly &lhs, const Term &t);
    // postcondition: returns a product poly

    friend Poly operator*(const Poly &lhs, const Poly &rhs);
    // postcondition: returns a product poly

    // precondition: rhs cannot be 0 x0
    friend Poly operator/(const Poly &lhs, const Poly &rhs);
    // postcondition: returns a quotient poly

    friend Poly operator%(const Poly &lhs, const Poly &rhs);
    // postcondition: returns a remainder poly

    friend ostream &operator<<(ostream &outs, const Poly &p);
    // postcondition: prints out p starting from higher exp

    // precondition: user types in a poly in the correct format
    friend istream &operator>>(istream &ins, Poly &p);
    // postcondition: p has been initialized with the input values

    double *get_coefs() const;
    int order() const { return _order; }
    void set_order(int new_order); // Not used!
    void fix_order();              // get rid of highest terms with zero coefs
private:
    int _order;
    double *_coefs;
};

#endif