#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include "assert.h"
#include <iostream>
#include <string>

using namespace std;

const int MINIMUM_CAPACITY = 3;

// precondition: a pointer has been created to be assigned a dynamic array
template <class T>
T *allocate(int capacity = MINIMUM_CAPACITY)
{
    // create a dynamic array of size "capacity"
    T *arr = new T[capacity];

    return arr; // return the pointer to that dynamic array
}
// postcondition: the pointer has been created

// precondition: source array and dynamic have been created
template <class T>
void copy_array(T *dest, const T *src, int many_to_copy)
{
    // create a walker that points to the start of the src array
    const T *walker_src = src;

    // create a walker that points to the start of the dest array
    T *walker_dest = dest;

    // iterate through the arrays
    for (int i = 0; i < many_to_copy; i++, walker_src++, walker_dest++)
    {
        *walker_dest = *walker_src; // anything at src will be assigned to
                                    // the variable walker_dest is pointing at
    }
}
// postcondition: the elements of source array have been copied to destination array

// precondition: a dynamic array has been initialzied
template <class T>
T *reallocate(T *a, int size, int capacity)
{
    T *arr_new = allocate<T>(capacity); // create a new dynamic array of size "capacity"
    copy_array(arr_new, a, size);       // copy the src array into the new array

    // tweak just for this assignment
    // fill the empty spaces with '0'
    for (int i = size; i < capacity; i++)
    {
        double *walker = arr_new + i;
        *walker = 0;
    }

    // delete the src array
    delete[] a;

    return arr_new; // return the pointer to the new array
}
// postcondition: the dynamic array has been resized to size 'capacity'

// precondition: an array has been created
template <class T>
void print_array(T *a, int size, int capacity = 0)
{

    // create a walker that points to the start of the array
    T *walker = a;

    cout << "(" << size << "/" << capacity << ")";

    cout << "[";
    // iterate over the array and print
    for (int i = 0; i < size; i++, walker++)
    {
        cout << *walker << "|";
    }
    cout << "]\n";
}
// postcondition: printed all the elements in the array

// precondition: an array has been created
template <class T>
void print(T *a, unsigned int how_many)
{

    // they are the same functions
    print_array(a, how_many);
}
// postcondition: printed all the elements in the array

// precondition: an array has been initialized, find_me index has
// been determined
template <class T>
T *search_entry(T *a, int size, const T &find_me)
{

    // create a walker that points to the start of the array
    T *walker = a;

    // iterate over the array and check
    for (int i = 0; i < size; i++, walker++)
    {
        if (*walker == find_me)
        {
            return walker; // return the pointer
        }
    }

    cout << "Element not found in the array";
    return nullptr; // if find_me wasn't found
}
// postcondition: the pointer to the found index or nullptr has been returned

// precondition: an array has been initialized, find_me index has
// been determined
template <class T>
int search(T *a, int size, const T &find_me)
{
    // create a walker that points to the start of the array
    T *walker = a;

    // iterate over the array and check
    for (int i = 0; i < size; i++, walker++)
    {
        if (*walker == find_me)
        {
            return i; // return the index
        }
    }

    cout << "Element not found in the array";
    return -1; // if find_me wasn't found
}
// postcondition: the index of find_me or -1 has been returned

// precondition: an array has been initialized
template <class T>
void shift_left(T *a, int &size, int shift_here)
{
    // if given index is negative
    assert(shift_here >= 0);

    // if index is out of range
    assert(shift_here < size);

    // walker pointing to the end of the array
    T *end = a + (size - 1);

    // create a walker that points to the index
    T *walker = a + shift_here;

    // create a second walker to that points to to the index
    // that comes after
    T *walker2 = walker + 1;

    while (walker != end)
    {
        *walker = *walker2;
        // move pointers to the right
        walker++;
        walker2++;
    }

    // reduce the size of the array
    size--;
}
// postcondition: all the elements after 'shift_here' have been shifted to left
// size of the array is decremented by 1

// precondition: an array has been initialized
template <class T>
void shift_left(T *a, int &size, T *shift_here)
{
    // calculate distance from the first element of the array and the shift_here element
    int distance = shift_here - a;

    shift_left(a, size, distance); // recall the already defined function
}
// postcondition: all the elements after 'shift_here' have been shifted to left
// size of the array is decremented by 1

// precondition: an array has been initialized
template <class T>
void shift_right(T *a, int &size, int shift_here)
{
    // if given index is negative
    assert(shift_here >= 0);

    // if index is out of range
    assert(shift_here < size);

    // pointer that points to the shift_here index
    T *shift_here_ptr = a + shift_here;

    // create a walker that points to one index after the end of the array
    T *walker = a + size;

    // create a second walker to that points to the end of the array
    T *walker2 = walker - 1;

    while (walker != shift_here_ptr)
    {
        *walker = *walker2;
        // move pointers to the left
        walker--;
        walker2--;
    }

    // increment the size of the array
    size++;
};
// postcondition: all the elements after 'shift_here' have been shifted to right
// size of the array is incremented by 1

// precondition: an array has been initialized
template <class T>
void shift_right(T *a, int &size, T *shift_here)
{
    // calculate distance from the first element of the array and the shift_here element
    int distance = shift_here - a;

    shift_right(a, size, distance); // recall the already defined function
};
// postcondition: all the elements after 'shift_here' have been shifted to right
// size of the array is incremented by 1

// precondition: source array and dynamic have been created
template <class T>
T *copy_array(const T *src, int size)
{
    T *arr_copy = new T[size];       // create a dynamic array of size "size"
    copy_array(arr_copy, src, size); // copy the src array into the arr_copy

    return arr_copy;
};
// postcondition: returned the destination array that has the copied elements
// of the source array

// precondition: an array has been created
template <class T>
string array_string(const T *a, int size)
{
    char character; // if it was array of characters
    // initialize the result string
    string result = "";

    // create a walker that walks through the array
    const T *walker = a;

    // iterate through the array
    for (int i = 0; i < size; i++, walker++)
    {
        // if the element is a character
        if (isalpha(*walker))
        {
            character = *walker;
            result = result + character + " ";
        }
        // if the element is an int, double or others
        else
        {
            result = result + to_string(*walker) + " ";
        }
    }

    return result;
}
// postcondition: returned the array as a string

// precondition: an array has been created
template <typename T>
void append_array(T *arr, int &size, T value)
{
    T *walker = arr + size;
    *walker = value;
    size++;
}
// postcondition: an element has been added to the back of the array. size has been incremented

#endif