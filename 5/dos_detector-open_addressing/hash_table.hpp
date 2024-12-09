/**
 * @file hash_table.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <cstdlib>
#include <cstdint>
#include <vector>
#include <functional>
#include <utility>
#include <memory>

#include "hash.hpp"
#include "hash_table_entry.hpp"

/**
 * @brief Implement the HashTable[K,V] ADT.
 *
 * @tparam K are the keys.
 * @tparam V are the values.
 *
 * @invariant load_factor() <= 0.5
 */

template <class K, class V>
class HashTable
{
public:
  /** @brief A reference to a hash table.*/
  typedef std::shared_ptr<HashTable<K, V>> Ref;

  /** @brief Functional type to do "key to std::uint64_t" conversions.*/
  typedef std::function<std::uint64_t(K)> Key_to_uint64_t;

  /** @name Life cicle.*/
  /** @{*/

  /**
   * @brief Create a new HashTable.
   * @param m is the table size.
   * @param key_to_int is the converter from key values to int value.
   * @param hash is the hash function.
   * @post not is_valid()
   * @post size()==m
   */
  HashTable(size_t m, Key_to_uint64_t const &key_to_int,
            OACollisionResolution::Ref hash);

  /** @}*/

  /** @name Observers*/
  /** @{*/

  /**
   * @brief Get the table size.
   * @return the size of the table.
   */
  size_t size() const;

  /**
   * @brief Return the load factor of the table.
   * @return the load factor.
   */
  float load_factor() const;

  /**
   * @brief Has the table this key?
   * @param k the key to find.
   * @return true if the key is saved into the table.
   * @warning The cursor is not affected by this operation.
   */
  bool has(K const &k) const;

  /**
   * @brief Find the table index where the key would be.
   * @return the table index where the key would be.
   * @post 0<=ret_v<size()
   */
  size_t find(K const &k) const;

  /**
   * @brief Get a table entry.
   *
   * @param idx is a table position.
   * @return return a const reference to the entry at the table position.
   * @pre 0<=idx<size()
   */
  HashTableEntry<K, V> const &entry(size_t idx) const;

  /**
   * @brief Get a table entry.
   *
   * @param k is the key to be found.
   * @return return a const reference to the value associated to the given key.
   * @pre has(k)
   */
  V const &operator[](K const &idx) const;

  /** @}*/

  /** @name Modifiers*/
  /** @{*/

  /**
   * @brief Insert a new entry.
   *
   * If the key is currently in the table, the value is updated.
   *
   * @return idx as the table index where the pair <k,v> is saved.
   * @post 0<=idx && idx<size()
   * @post entry(find(k)).is_valid()
   * @post entry(find(k)).get_key()==k
   * @post entry(find(k)).get_value()==v
   */
  size_t insert(K const &k, V const &v);

  /**
   * @brief Remove the entry at the cursor position.
   * @pre entry(idx).is_valid()
   * @post !entry(idx).is_valid()
   * @post !has(old entry(idx).get_key())
   */
  void remove(size_t idx);

  /**
   * @brief Get a table entry.
   *
   * @param idx is a table position.
   * @return return a reference to the entry at the table position.
   * @pre 0<=idx<size()
   */
  HashTableEntry<K, V> &entry(size_t idx);

  /**
   * @brief Get the value associated to a given key.
   * @warning if a entry <k,v> doesn't exists, a new entry is created.
   * @param k is the key to be found.
   * @return return a reference to the value associated to the given key.
   */
  V &operator[](K const &idx);

  /** @} */

protected:
  /**
   * @brief Generate a new table with doble size when load factor > 0.5
   * @return the table size (the old size if growing was not necessary).
   * @post load_factor()<=0.5
   */
  size_t rehash();

  Key_to_uint64_t key_to_int_;              /**< Convert key values to int.*/
  OACollisionResolution::Ref hash_;         /**< The hash function.*/
  std::vector<HashTableEntry<K, V>> table_; /**< The table.*/
  size_t used_entries_;                     /**< Counter for the used entries (valid and deleted).*/
};

#include "hash_table_imp.hpp"
