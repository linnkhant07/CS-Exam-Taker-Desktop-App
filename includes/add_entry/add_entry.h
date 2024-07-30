#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include "../../includes/array_functions/array_functions.h"
#include <iostream>
#include "string.h"
using namespace std;


template<class T>
T* add_entry(T* list, const T& new_entry,int& size, int& capacity);
template<class T>
T* remove_entry(T* list, const T& delete_me,int& size, int& capacity);

template <class T>
T *remove_last_entry(T *list, T &popped,int &size, int &capacity);

template <class T>
T *insert_entry(T *list, const T &insert_this, int insert_here,int &size,int &capacity);

template <class T>
T *erase_entry(T *list, int index,int &size, int &capacity);

//!DECLARATION
//========================================================

template<class T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity){
    if (size==capacity){
        capacity= capacity*2;
       list= reallocate (list, size, capacity);
    }
    append (list, size, new_entry);
    return list;
}
template<class T>
T* remove_entry(T* list, const T& delete_me,int& size, int& capacity){
    
    T* killer=search_entry (list,size,delete_me);
    if (killer==nullptr){
        return list;
    }
    shift_left (list, size, killer);
    int tester = capacity/4;
    if (size==tester){
        // cout<<"Reducing, remember to remove entry\n";
        capacity/=2;
        list = reallocate (list, size,capacity);
    }
    return list;
 }

template <class T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity){

    T* last=(list+size)-1;
    popped=*last;
    list= erase_entry (list,size,size,capacity);
    return list;

}

template <class T>
T *insert_entry(T *list, const T &insert_this,int insert_here,int &size,int &capacity){
    if (size==capacity){
        capacity= capacity*2;
       list= reallocate (list, size, capacity);
    }
    shift_right (list,size,insert_here);
    T* p = list+insert_here;
    *p=insert_this;
    return list;
    }

template <class T>
T *erase_entry(T *list, int index, int &size, int &capacity){
    assert (size!=0);
    T* killer=list+index;
    shift_left (list, size, killer);
    int tester = capacity/4;
    if (capacity == 6){
        return list;
    }
    if (size==tester){
        // cout<<"Reducing\n";
        capacity=capacity/2;
        // cout<<capacity<<"\n";
        list = reallocate (list, size,capacity);
// return list;
    }
    return list;
}

#endif