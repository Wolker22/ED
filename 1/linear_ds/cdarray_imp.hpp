/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <sstream>
#include <cassert>
#include "cdarray.hpp"

template <class T>
CDArray<T>::CDArray(size_t cap)
{
    assert(cap > 0);
    // TODO

    _data = std::shared_ptr<T>(new T[cap]);
    _capacity = cap;
    _size = 0;
    _front = 0;
    _back = 0;

    //
    assert(capacity() == cap);
    assert(is_empty());
    assert(size() == 0);
}

template <class T>
CDArray<T>::~CDArray()
{
    // TODO
    // Remember: depending on your representation, it is possible that nothing
    // must be done.

    //
}

template <class T>
typename CDArray<T>::Ref
CDArray<T>::create(size_t cap)
{
    return std::make_shared<CDArray<T>>(cap);
}

template <class T>
typename CDArray<T>::Ref
CDArray<T>::create(std::istream &in) noexcept(false)
{
    auto ret_v = std::make_shared<CDArray<T>>(1);
    // TODO
    // Hint: use std::istringstream to convert from "string" to template
    //  parameter T type.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.

    std::string token;
    in >> token;
    if (token != "["){
        if (token == "[]"){
            return ret_v;
        }
        throw std::runtime_error("Wrong input format.");
    }

    in >> token;
    while (token != "]"){
        std::istringstream ifs(token);
        T item;
        ifs >> item;
        if (!ifs){
            throw std::runtime_error("Wrong input format.");
        }
        ret_v->push_back(item);

        in >> token;
        if (!in){
            throw std::runtime_error("Wrong input format.");
        }
    }
    //
    return ret_v;
}

template <class T>
bool CDArray<T>::is_empty() const
{
    bool ret_v = false;
    // TODO
    if (_size == 0){
        ret_v = true;
    }
    //
    return ret_v;
}

template <class T>
bool CDArray<T>::is_full() const
{
    bool ret_v = false;
    // TODO
    if (_size == _capacity){
        ret_v = true;
    }
    //
    assert(!ret_v || size() == capacity());
    return ret_v;
}

template <class T>
size_t
CDArray<T>::capacity() const
{
    size_t ret_v = 0;
    // TODO
    ret_v = _capacity;
    //
    return ret_v;
}

template <class T>
size_t
CDArray<T>::size() const
{
    size_t ret_v = 0;
    // TODO
    ret_v = _size;
    //
    return ret_v;
}

template <class T>
std::ostream &CDArray<T>::fold(std::ostream &out) const
{
    // TODO

    out << "[ ";

    for (size_t p = 0; p < _size; ++p)
    {
        out << get(p) << " ";
    }

    out << "]";

    return out;
}

template <class T>
T CDArray<T>::get(size_t pos) const
{
    T ret_v;
    // TODO
    ret_v = _data.get()[(_front + pos) % _capacity];

    //
    return ret_v;
}

template <class T>
void CDArray<T>::set(size_t pos, T const &new_v)
{
    // TODO
    _data.get()[(_front + pos) % _capacity] = new_v;

    //
    assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size)
{
    size_t ret_v;
    // TODO
    ret_v = (v + 1) % size;
    //
    return ret_v;
}

size_t cDec(size_t v, size_t size)
{
#ifndef NDEBUG
    size_t old_v = v;
#endif
    size_t ret_v;
    // TODO
    // Remember: v is a unsigned value, so you must cast to signed before decrementing
    ret_v = (v - 1 + size) % size;

    //
    assert(old_v == cInc(ret_v, size));
    return ret_v;
}

template <class T>
void CDArray<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_front = is_empty() ? T() : get(0);
#endif
    // TODO
    if (is_full())
    {
        grow();
    }

    for (size_t i = size(); i > 0; --i)
    {
        set(i, get(i - 1));
    }

    set(0, new_it);
    ++_size;

    //
    assert(size() == old_size + 1);
    assert(get(0) == new_it);
    assert(old_is_empty || (get(1) == old_front));
}

template <class T>
void CDArray<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_back = is_empty() ? T() : get(size() - 1);
#endif
    // TODO
    if (is_full())
    {
        grow();
    }
    set(_size, new_it);
    ++_size;

    //
    assert(size() == old_size + 1);
    assert(get(size() - 1) == new_it);
    assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T>
void CDArray<T>::pop_front()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_front = size() > 1 ? get(1) : T();
#endif
    // TODO
    if (!is_empty())
    {
        for (size_t i = 0; i < _size - 1; ++i)
        {
            set(i, get(i + 1));
        }
        --_size;
    }
    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(0) == old_next_front);
}

template <class T>
void CDArray<T>::pop_back()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
    // TODO
    if (!is_empty())
    {
        --_size;
    }
    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T>
void CDArray<T>::insert(size_t pos, T const &v)
{
    assert(pos < size()); // Verificar si pos está dentro del rango válido del arreglo

#ifndef NDEBUG
    size_t old_size = size();
    T old_back = get(size() - 1);
    T old_pos_v = get(pos);
#endif

    if (is_full())
    {
        grow();
    }

    if (pos == 0)
    {
        push_front(v);
    }
    else
    {
        for (size_t p = size(); p != pos; --p)
        {
            set(p, get(p - 1));
        }

        set(pos, v);
        _back = cInc(_back, _capacity);
        ++_size;
    }

    // Verificaciones de debug
    assert(size() == old_size + 1);
    assert(get(pos) == v);
    assert(get(pos + 1) == old_pos_v);
    assert(get(size() - 1) == old_back);
}

template <class T>
void CDArray<T>::remove(size_t pos)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
    // TODO
    for (size_t p = pos; p < size() - 1; ++p)
    {
        set(p, get(p + 1));
    }
    if (pos == size() - 1)
    {
        _back = cDec(_back, _capacity);
    }
    --_size;
    //
    assert(size() == old_size - 1);
    assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T>
void CDArray<T>::grow()
{
#ifndef NDEBUG
    size_t old_capacity = capacity();
#endif
    // TODO
    size_t new_capacity = capacity();
    new_capacity = new_capacity * 2;
    std::shared_ptr<T> new_data = std::shared_ptr<T>(new T[new_capacity]);
    _capacity = new_capacity;

    for (auto i = 0; i < _size; ++i)
    {
        new_data.get()[i] = get(i);
    }

    _data = new_data;
    _front = 0;
    _back = _size - 1;
    //
    assert(capacity() == 2 * old_capacity);
}