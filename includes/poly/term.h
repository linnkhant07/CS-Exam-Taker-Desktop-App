#ifndef TERM_H
#define TERM_H
using namespace std;

struct Term
{
    double _coef;
    int _exp;

    // precondition: exp cannot be negative
    Term(double coef, int exp);

    // precondition: lhs and rhs
    friend bool operator==(const Term &lhs, const Term &rhs);
    // postcondition: returned true if lhs and rhs are equal

    // precondition: lhs and rhs
    friend bool operator!=(const Term &lhs, const Term &rhs);
    // postcondition: returned false if lhs and rhs are equal

    // precondition: lhs and rhs
    friend bool operator>(const Term &lhs, const Term &rhs);
    // postcondition: returned true if lhs > rhs

    // precondition: lhs and rhs
    friend bool operator<(const Term &lhs, const Term &rhs);
    // postcondition: returned true if lhs < rhs

    // precondition: lhs and rhs
    friend Term operator+(const Term &lhs, const Term &rhs);
    // postcondition: returns a sum poly

    // precondition: lhs and rhs
    friend Term operator-(const Term &t);
    // postcondition: returns a new summed poly

    // precondition: lhs and rhs
    friend Term operator-(const Term &lhs, const Term &rhs);
    // postcondition: returns a new subtracted poly

    // precondition: lhs and rhs
    friend Term operator*(const Term &lhs, const Term &rhs);
    // postcondition: returns a new product poly

    // precondition: rhs is not 0 x^0
    friend Term operator/(const Term &lhs, const Term &rhs);
    // postcondition: returns a new quotient poly

    friend ostream &operator<<(ostream &outs, const Term &t);
};

#endif