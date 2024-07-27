#ifndef POLY_STUDENT_CPP
#define POLY_STUDENT_CPP

#include <iostream>
#include <iomanip>
#include <math.h>
#include "poly.h"
#include "../array_functions/array_functions.h"

using namespace std;

Poly operator%(const Poly &lhs, const Poly &rhs)
{
    // student has to write this
    
    
    Poly div = lhs / rhs;
    return lhs - div * rhs;

    return lhs;
}

#endif
