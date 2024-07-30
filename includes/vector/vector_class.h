#ifndef VECTOR_CLASS_H_
#define VECTOR_CLASS_H_

#include <iostream>
#include <ostream>
#include "../../includes/array_functions/array_functions.h"
#include "../../includes/add_entry/add_entry.h"
using namespace std;

template <class T>
class Vector{
public:

    Vector(int cap = 100);
    Vector(T *arr, int size);

    //* big three:
    Vector (const Vector& other );
    ~Vector ();
    Vector& operator = (const Vector& RHS);

    //member access functions:
    T& operator [](int index);
    const T& operator [](int index) const;

    T& at(int index);              //return reference to item at position index
    const T& at(int index) const;  //return a const item at position index

    T& front();                         //return item at position 0.
    T& back();                          //return item at the last position


    //Push and Pop functions:
    Vector& operator +=(const T& item); //push_back
    void push_back(const T& item);      //append to the end
    T pop_back();                       //remove last item and return it


    //Insert and Erase:
    void insert(int insert_here, const T& insert_this); //insert at pos
    void erase(int erase_this_index);        //erase item at position
    int index_of(const T& item);             //search for item. retur index.

    //size and capacity:
    void set_size(int size);              //enlarge the vector to this size
    void set_capacity(int capacity);      //allocate this space
    int size() const ;  //return _size
    int capacity() const ; //return _capacity

    bool empty() const;                    //return true if vector is empty
    string string_vector () const;
    //OUTPUT:
    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& _a);
private:
    int _size;
    int _cap;
    T* _point;
};
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================
//!!!!===========================================================================================


   template <class T>
    Vector<T>::Vector(int cap){
        _cap = cap;
        _point = allocate <T> (cap);
        _size = 0;

    }
    template <class T>
    Vector<T>::Vector(T *arr, int size){
        _size = size;
        _cap = 3;
        while (_cap<_size){
            _cap*=2;
        }
        // _point=copy_array <T> (arr, size);
        _point = allocate<T>(_cap);
        copy_array(_point, arr, size);
    }

    //* big three:
    template <class T>
    Vector<T>::Vector(const Vector& other ){
        _point = allocate <T>  (other.capacity());
        copy_array <T> (_point, other._point, other.size());
        _cap = other.capacity ();
        _size=other.size ();
    }
    template <class T>
    Vector<T>::~Vector (){
        _size=0;
        _cap=0;
        delete [] _point;
        _point=nullptr;
    }
    template <class T>
    Vector<T>& Vector<T>::operator=(const Vector& RHS){
        if (this == &RHS){
            return *this;
        }
        if (_point != nullptr)
        delete[] this->_point;

        this->_cap = RHS.capacity ();
        this->_size = RHS.size();
        this->_point=allocate <T> (_cap);
        copy_array (_point, RHS._point, RHS.size());
        return *this;
    }

    //member access functions:
    template <class T>
    T& Vector<T>::operator[](int index){
        return *(_point+index);
    }
    template <class T>
    const T& Vector<T>::operator[](int index) const{
        return *(_point+index);
    }
    
    template <class T>
    T& Vector<T>::at(int index){
        return *(_point+index);
    }                  //return reference to item at position index
    template <class T>
    const T& Vector<T>::at(int index) const{
        return *(_point+index);
    }  //return a const item at position index
    
    template <class T>
    T& Vector<T>::front(){
        return *_point;
    }                      //return item at position 0.
    template <class T>
    T& Vector<T>::back(){
        return *(_point+_size-1);
    }                        //return item at the last position


    //Push and Pop functions:
    
    template <class T>
    Vector<T>& Vector<T>::operator+=(const T& item){
        _point = add_entry <T>(_point,item, _size, _cap);
        return *this;
    } 
    //push_back
    template <class T>
    void Vector<T>::push_back(const T& item){
        _point=add_entry <T> (_point, item, _size, _cap);
    }      
    //append to the end
    template <class T>
    T Vector<T>::pop_back(){
        T value;
        _point=remove_last_entry <T> (_point, value, _size, _cap);
//        cout<<"Removed last entry\n";
//        print_array (_point, _size, _cap);
        return value;
    }                       //remove last item and return it


    //Insert and Erase:
    template <class T>
    void Vector<T>::insert(int insert_here, const T& insert_this){
        _point=insert_entry <T> (_point, insert_this, insert_here, _size, _cap);
    } //insert at pos
    
    template <class T>
    void Vector<T>::erase(int erase_this_index){
        _point = erase_entry <T> (_point, erase_this_index,_size,_cap);
        if (_size==0)
        _point= nullptr;
    }        //erase item at position
    template <class T>
    int Vector<T>::index_of(const T& item){
        return search <T> (_point, _size,item);
    }             //search for item. retur index.

    //size and capacity:
    template <class T>
    void Vector<T>::set_size(int size){
        _size=size;
        if (_size > _cap){
            _cap*2;
        }
    }              //enlarge the vector to this size
    template <class T>
    void Vector<T>::set_capacity(int capacity){
        _cap = capacity;
        _point=reallocate <T> (_point, _size, _cap);
    }      //allocate this space

    template <class T>
    int Vector<T>::size() const {
        return _size;
    }  //return _size
    
    template <class T>
    int Vector<T>::capacity() const {
        return _cap; 
    } 

    template <class T>
    bool Vector<T>::empty() const{
    if (_size ==0){
        return true;
    }        
    return false;
    }                   //return true if vector is empty
    
    template <class T>
    string Vector<T>::string_vector () const{
        string result = array_string (_point,_size);
        return result;
    }

    //OUTPUT:
    template <class U>
    ostream& operator<<(ostream& outs, const Vector<U>& _a){
        print_array (_a._point, _a.size(), _a.capacity(),outs);
        cout<<"\n";
        return outs;
    }    



#endif // VECTOR_CLASS_H_