#ifndef ARRAY_H
#define ARRAY_H

#include <iostream> 
#include "Exception.h"

using namespace std;

template <typename T>
class Array {
private:
    T* m_array;
    int m_start_index;
    int m_length;
public:
    Array(); // Default ctor
    ~Array(); // Destructor
    Array(int length, int index = 0); // 1 or 2 argument ctor
    Array(const Array<T>& copy); // cpy ctor
    Array(Array<T>&& copy); // move ctor

    Array& operator =(const Array<T>& rhs); // copy assignment
    Array& operator =(const Array<T>&& rhs);// move assignment
    T& operator[] (const int index); // array index operator

    int getStartIndex();
    int getLength();
    void setStartIndex(const int index);
    void setLength(const int length);
};

template <typename T>
Array<T>::Array() : m_array(nullptr), m_start_index(0), m_length(0) { }

template<typename T>
Array<T>::Array(int length, int index)
{
    if (length < 0)
        throw(Exception("You cannot make length a negative number!"));

    m_array = new T[length];
    m_length = length;
    m_start_index = index;
}

template<typename T>
Array<T>::Array(const Array<T>& copy)
{
    m_start_index = copy.m_start_index;
    m_length = copy.m_length;
    m_array = new T[m_length];

    for (int i = 0; i < m_length; i++)
        m_array[i] = copy.m_array[i];
}

template<typename T>
Array<T>::Array(Array<T>&& copy)
{
    if (this != &copy)
    {
        delete[] m_array;
        m_array = nullptr;

        if (copy.m_array != nullptr)
        {
            m_array = new T[copy.m_length];
            m_length = copy.m_length;

            for (int i = 0; i < copy.m_length; i++)
                m_array[i] = copy.m_array[i];
        }
    }
    delete[]copy.m_array;
    copy.m_array = nullptr;
    copy.m_length = 0;
    copy.m_start_index = 0;

}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& rhs)
{
    if (this != &rhs)
    {
        delete[] m_array;
        m_array = nullptr;

        if (rhs.m_array != nullptr)
        {
            m_array = new T[rhs.m_length];
            m_length = rhs.m_length;

            for (int i = 0; i < rhs.m_length; i++)
                m_array[i] = rhs.m_array[i];
            // copy all elements of the object array to the new object
        }
    }
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>&& rhs)
{
    if (this != &rhs)
    {
        delete[] m_array;
        m_array = nullptr;
        if (rhs.m_array != nullptr)
        {
            m_array = new T[rhs.m_length];
            m_length = rhs.m_length;

            for (int i = 0; i < rhs.m_length; i++)
                m_array[i] = rhs.m_array[i];
            // move all elements of the object array to the new object
        }
    }
    delete[]rhs.m_array;
    rhs.m_array = nullptr;
    rhs.m_length = 0;
    rhs.m_start_index = 0;
    // delete and initialize all values of the rhs object 

    return *this;
}

template<typename T>
T& Array<T>::operator[] (const int index)
{
    int offset_index = index - m_start_index;
    int neg_offset_index = index + (-1 * m_start_index);
    if (m_start_index > 0)
        return m_array[offset_index];
    // if the array start index is positive, we adjust to make it a correct index value
    else if (m_start_index < 0)
        return m_array[neg_offset_index];
    // if the array start index is negative, we adjust to make it a correct index value
    if (index > m_length || index < 0)
        throw(Exception("Index out of bounds"));
    return m_array[index];
}

template<typename T>
int Array<T>::getStartIndex()
{
    return m_start_index;
}

template<typename T>
int Array<T>::getLength()
{
    return m_length;
}

template<typename T>
void Array<T>::setStartIndex(const int index)
{
    m_start_index = index;
}

template<typename T>
void Array<T>::setLength(const int length)
{
    if (length < 0)
        throw(Exception("You cannot make length a negative number!"));

    T* temp_m_array = new T[length];

    for (int i = 0; i < length; i++) {
        if (i < m_length)
            temp_m_array[i] = m_array[i];
        else
            temp_m_array[i] = {};
        // zero initialization for the rest of the unfilled elements
    }

    delete[] m_array;
    m_array = temp_m_array;
    m_length = length;
}

template<typename T>
Array<T>::~Array()
{
    delete[] m_array;
}

#endif
