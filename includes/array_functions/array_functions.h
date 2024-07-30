#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include "array_functions.h"
#include <typeinfo>
#include "iomanip"
#include "iostream"
#include "string.h"
#include <cassert>
using namespace std;

const int MINIMUM_CAPACITY = 3;

template <class T>
T *allocate(int capacity = MINIMUM_CAPACITY); // allocate 'capacity'
                                              //       elements.
                                              //   return array

template <class T>
T *reallocate(T *a, int size, int capacity); // take array, resize it
                                             //   return new array.
                                             //   delete old array

template <class T>
void print_array(T *a, int size, int capacity = 0, ostream &outs = cout); // prints
                                                                          //   (size/capacity)
                                                                          //   for debugging

template <class T>
void print(T *a, unsigned int how_many,
           ostream &outs = cout); // print array

template <class T>
T *search_entry(T *a, int size, const T &find_me); // search for 'find me'

template <class T>
int search(T *a, int size, const T &find_me); // search for 'find_me'

template <class T>
void shift_left(T *a, int &size, int shift_here); // shift left @ pos:
                                                  //     erases @ pos
template <class T>
void shift_left(T *a, int &size, T *shift_here); // shift left @ pos:
                                                 //     erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here); // shift right:
                                                   //       make a hole

template <class T>
void shift_right(T *a, int &size, T *shift_here); // shift right:
                                                  //    make a hole

template <class T>
void copy_array(T *dest, const T *src, int many_to_copy); // copy from src to dest

template <class T>
T *copy_array(const T *src, int size); // return a
//  copy of src
template <class T>
void append(T *a, int &size, T append_me);

template <class T>
string array_string(const T *a, int size); // return array
                                           //   as a string
//========================================================================
//! TEST PURPOSE
//========================================================================
//========================================================================

template <class T>
void filler(int size, T *a);

template <class T>
void filler2(int size, T *a, char whole);

template <class T>
bool comparing(T *list, T *a, int size);

//========================================================================

template <class T>
void filler(int size, T *a)
{
    T *walkman = a;
    for (int i = 0; i < size; i++, walkman++)
    {
        *walkman = i;
    }
}

template <class T>
void filler2(int size, T *a, char whole)
{
    T *walkman = a;
    for (int i = 0; i < size; i++, walkman++)
    {
        *walkman = whole;
    }
}

template <class T>
bool comparing(T *list, T *a, int size)
{
    T *walkman = list;
    T *b = a;
    for (int i = 0; i < size; i++, walkman++, b++)
    {
        if (*a != *list)
        {
            return false;
        }
    }
    return true;
}

//========================================================================
//========================================================================

template <class T>
T *allocate(int capacity)
{
    assert(capacity != 0);
    T *a = new T[capacity];
    // bool debug = false;
    // if (debug){
    // T*walkman=a;
    // int size =5;
    // for (int i = 0; i < size ; i++)
    // {
    //     *walkman=i;
    //     walkman++;
    // }
    // }

    return a;
} // allocate 'capacity'
  //       elements.
  //   return array

template <class T>
T *reallocate(T *a, int size, int capacity)
{
    assert(capacity != 0);
    T *b = allocate<T>(capacity);

    copy_array(b, a, size);

    delete[] a;
    return b;
} // take array, resize it
  //   return new array.
  //   delete old array

template <class T>
void print_array(T *a, int size, int capacity, ostream &outs)
{
    //! dumb assumption
    // TODO has to be changed after consultation
    cout << " {  " << size << "/" << capacity;
    print(a, size);
    cout << "  }";
    cout << "\n";
} // prints
  //   (size/capacity)
  //   for debugging

template <class T>
void print(T *a, unsigned int how_many, ostream &outs)
{
    T *walkman = a;
    for (int i = 0; i < how_many; i++, walkman++)
    {
        cout << " | " << *walkman << " | ";
    }

} // print array

template <class T>
T *search_entry(T *a, int size, const T &find_me)
{
    T *walkman = a;
    for (int i = 0; i < size; i++, walkman++)
    {
        if (*walkman == find_me)
        {
            return walkman;
        }
    }
    return nullptr;
    // returns pointer of the memory location of find_me
} // search for 'find me'

template <class T>
int search(T *a, int size, const T &find_me)
{
    T *walkman = a;
    for (int i = 0; i < size; i++, walkman++)
    {
        // cout<<i<<" ";
        if (*walkman == find_me)
        {
            return i;
        }
    }
    return -1;
} // search for 'find_me'

template <class T>
void shift_left(T *a, int &size, int shift_here)
{
    if (shift_here <= size && shift_here >= 0)
    {
        T *walkman = a + (shift_here);
        shift_left(a, size, walkman);
    }
    else
    {
        cout << "Cannot shift left\n";
        return;
    }
} // shift left @ pos:
  //     erases @ pos
template <class T>
void shift_left(T *a, int &size, T *shift_here)
{
    if (shift_here <= a + size && shift_here >= a)
    {
        T *limit = a + (size - 1);
        int count = limit - shift_here;
        T *walkman = shift_here;
        for (int i = 0; i < count; i++, walkman++)
        {
            T *tempo = (walkman + 1);
            *walkman = *tempo;
        }
        size--;
    }
    else
    {
        cout << "Cannot shift left\n";
        return;
    }
}
//    erases @ pos
template <class T>
void shift_right(T *a, int &size, int shift_here)
{
    if (shift_here <= size && shift_here >= 0)
    {
        T *limit = a + shift_here;
        shift_right(a, size, limit);
    }
    else
    {
        cout << "Cannot shift right\n";
        return;
    }
} //      make a hole

template <class T>
void shift_right(T *a, int &size, T *shift_here)
{
    if (shift_here >= a && shift_here <= a + size)
    {
        size++;
        T *walkman = (a + size - 1);
        int count = walkman - shift_here;
        for (int i = 0; i < count; i++, walkman--)
        {
            T *tempo = (walkman - 1);
            *walkman = *tempo;
        }
    }
    else
    {
        cout << "Cannot shift right\n";
        return;
    }
} // shift right:
  //    make a hole

template <class T>
void copy_array(T *dest, const T *src, int many_to_copy)
{
    assert(!(src == nullptr));
    if (dest == nullptr)
    {
        dest = allocate<T>(many_to_copy);
    }
    T *dest_ptr = dest;
    const T *src_ptr = src;
    // const T* n_src =  src;
    int i = many_to_copy;
    while (i > 0)
    {
        *dest_ptr = *src_ptr;
        src_ptr++;
        dest_ptr++;
        i--;
    }
} // copy from src to dest

template <class T>
T *copy_array(const T *src, int size)
{
    T *a = allocate<T>(size);
    const T *n_src = src;
    copy_array(a, n_src, size);
    return a;
} // return a
  //   copy of src
template <class T>
void append(T *a, int &size, T append_me);

template <class T>
string array_string(const T *a, int size)
{
    string test = "";
    const T *walkman = a;
    for (int i = 0; i < size; i++, walkman++)
    {
        if (typeid(char) != typeid(*walkman))
            test += to_string(*walkman);
        else
            test += *walkman;
    }
    return test;
} // return array
  //   as a string

#include "student.cpp"

#endif