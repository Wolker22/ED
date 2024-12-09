/**
 * @file hash_table_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#ifdef __DEBUG__
#include <iomanip>
#include <iostream>
#endif

#include <cassert>

#include "hash_table.hpp"

template <class K, class V>
HashTable<K, V>::HashTable(size_t m,
                           const Key_to_uint64_t &key_to_int,
                           OACollisionResolution::Ref hash)
{
    assert(m == hash->m());
    // TODO
    key_to_int_=key_to_int;//estamos dandole un valor a la clave para ubicar la en la tabla
    used_entries_=0;//establecemos el numero de entradas 0 porque esta vacio
    table_=std::vector<HashTableEntry<K, V>>(m);//generamos un vector m
    hash_=hash;//igualamos el hash al nuestro para poder llamar a las funciones hash
    //
    assert(size() == m);
}

template <class K, class V>
size_t
HashTable<K, V>::size() const
{
    size_t ret_v = 0;
    // TODO
    ret_v=table_.size();
    //
    return ret_v;
}

template <class K, class V>
float HashTable<K, V>::load_factor() const
{
    float ret_v = 0.0f;
    // TODO

    ret_v=(float)used_entries_/table_.size();//calculamos el factor entre el numero de entradas entre el tamaño total en float

    //
    return ret_v;
}

template <class K, class V>
bool HashTable<K, V>::has(K const &k) const
{
    bool ret_v = false;
    // TODO
    //  Hint: use the find method.
    auto idx=find(k);
    if(table_[idx].is_valid()){//nos vamos a la posicion idx que se encuentra usando find sobre la tabla con nuestra clave, si se encuentra el estado sera valido si no, no
        ret_v=true;
    }
    //
    return ret_v;
}

template <class K, class V>
size_t HashTable<K, V>::find(K const &k) const
{
    assert(load_factor() < 1.0f);
    size_t idx = 0;
    size_t iter=0;//declaramos un iter para poder llamar a la funcion hash que calcule la posicion
    auto key=key_to_int_(k);//de esta manera convertimos una clave en entero
    do{   
        idx=(*hash_)(key, iter);//calculamos la posicon mediante el operator ()
        iter++;
    }while(!table_[idx].is_empty()&&!(table_[idx].key()==k));//mientras que la posicion hayada no este vacia que quiere decir que no esta y mientras el que ha encontrado exista pero no sea k
    //
    assert(0 <= idx && idx < size());
    return idx;
}

template <class K, class V>
size_t HashTable<K, V>::insert(K const &k, V const &v)
{
    assert(load_factor() <= 0.5f);
    size_t idx = 0;
    // TODO
    // Remember: increment the number of used entries only when an
    // empty entry was used.

    idx=find(k);

    if(table_[idx].is_empty()){
        used_entries_++;
    }

    table_[idx].set(k, v);

    if(load_factor()>0.5){
        rehash();
        idx=find(k);
    }
    //
    assert(idx < size());
    assert(entry(idx).is_valid());
    assert(entry(idx).key() == k);
    assert(entry(idx).value() == v);
    assert(load_factor() <= 0.5f);
    return idx;
}

template <class K, class V>
void HashTable<K, V>::remove(size_t idx)
{
#ifndef NDEBUG
    assert(entry(idx).is_valid());
    K old_k = entry(idx).key();
#endif
    // TODO
    // Remember: we are using a mark to sign "deleted".

    table_[idx].set_deleted();

    //
    assert(!entry(idx).is_valid());
    assert(!has(old_k));
}

template <class K, class V>
size_t HashTable<K, V>::rehash()
{
    // TODO
    // Remember: rehash when load_factor > 0.5
    // Remember: we use a 2 factor to grown the current size.
    // Remember: a new hash function will be picked at random from the Universal Family.
    // Remember: reset the number of used entries to zero before inserting the old valid
    // entries in the new table.

    auto oldtable = table_;

    table_=std::vector<HashTableEntry<K, V>>(2*oldtable.size());

    hash_=hash_->pick_at_new(table_.size());
    used_entries_=0;

    for(size_t i=0; i<oldtable.size(); i++){
        if(oldtable[i].is_valid()){
            insert(oldtable[i].key(), oldtable[i].value());
        }
    }

    //
    assert(load_factor() <= 0.5);
    return size();
}

template <class K, class V>
HashTableEntry<K, V> const &HashTable<K, V>::entry(size_t idx) const
{
    assert(idx < size());
    // TODO: recode according to your representation.

    return table_[idx];
    //
}

template <class K, class V>
HashTableEntry<K, V> &HashTable<K, V>::entry(size_t idx)
{
    assert(idx < size());
    // TODO: recode according to your representation.

    return table_[idx];
    //
}

template <class K, class V>
V const &HashTable<K, V>::operator[](K const &k) const
{
    assert(has(k));
    // TODO: recode according to your representation.
    auto idx = find(k);
    return table_[idx];
    //
}

template <class K, class V>
V &HashTable<K, V>::operator[](K const &k)
{
    // TODO: recode according to your representation.
    // Remember: if an entry exits for the key, return a reference to its value,
    // else insert a new entry pair <k, _> and return a reference to its value.
    auto idx = find(k);
    if(table_[idx].is_empty()){
        table_[idx].set(k, V());
    }
    return table_[idx];
    //
}