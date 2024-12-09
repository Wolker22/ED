/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <iostream>
#include <memory>
#include <functional>

/** @brief a Double linked node.*/
template <class T>
class DNode
{
public:
  /** @brief Define a shared reference to a DNode.
   * Manages the storage of a pointer, providing a limited garbage-collection
   * facility, possibly sharing that management with other objects.
   * @see http://www.cplusplus.com/reference/memory/shared_ptr/
   */
  typedef std::shared_ptr<DNode<T>> Ref;

  /**
   * @brief Define a shared reference to a data item.
   * Manages the storage of a pointer, providing a limited garbage-collection
   * facility, possibly sharing that management with other objects.
   * @see http://www.cplusplus.com/reference/memory/shared_ptr/
   */
  typedef std::shared_ptr<T> ItemRef;

  /** @name Life cycle.*/
  /** @{*/

  /** @brief Create a dummy node.
   *  A dummy node has not item data used to mark the "end" of the sequence.   *
   *  @post is_dummy()
   *  @post next()==prev()==this
   */
  DNode();

  /** @brief Create a node.
   *  @post it == item()
   *  @post next()==nullptr
   *  @post prev()==nullptr
   *  @post !is_dummy()
   */
  DNode(T const &it);

  /**
   * @brief Create a dummy node using dynamic memory.
   * @return a shared reference to the dummy node.
   * @post ret_v->is_dummy()
   */
  static typename DNode<T>::Ref create();

  /**
   * @brief Create a DNode using dynamic memory.
   * @param it the value save in the node.
   * @return a shared reference to the new node.
   */
  static typename DNode<T>::Ref create(T const &it);

  /** @brief Destroy a DNode.**/
  ~DNode();

  /** @}*/

  /** @name Observers.*/
  /** @{*/

  /**
   * @brief Is it a dummy node?
   * A dummy node is a node which does not contain any data. Usually it is
   * used to mark the end of a list.
   * @return true when it is.
   */
  bool is_dummy() const;

  /** @brief Get the data item.*/
  T item() const;

  /**
   * @brief Get the link to next element.
   */
  typename DNode<T>::Ref prev() const;

  /** @brief Get the link to next element.*/
  typename DNode<T>::Ref next() const;

  /** @}*/

  /** @name Modifiers.*/
  /** @{*/

  /** @brief Set the data item.*/
  void set_item(const T &new_it);

  /** @brief Set the link to the next node.*/
  void set_prev(DNode<T>::Ref prev);

  /** @brief Set the link to the next node.*/
  void set_next(DNode<T>::Ref next);

  /** @}*/

protected:
  // TODO: give a representation
  DNode<T>::ItemRef _item;
  DNode<T>::Ref _prev;
  DNode<T>::Ref _next;
  //
};











/**Forward declaration.*/
template <class T>
class List;

/**
 * @brief Models an iterator to edit a list.
 *
 * @tparam T the type of the items in the list.
 */
template <class T>
class ListIterator
{
public:
  /**
   * @brief Destroy the List Iterator object.
   *
   */
  ~ListIterator();

  typedef ListIterator<T> iterator;

  /** @name Observers.*/
  /** @{*/

  /**
   * @brief Is the iterator pointing to a node?
   */
  bool is_valid() const;

  /**
   * @brief Get item in the iterator position.
   *
   * @return item in the iterator position.
   * @pre is_valid()
   */
  T item() const;

  /**
   * @brief Get an iterator in a next position.
   *
   * @param dist number of next positions.
   * @return an iterator in a next position.
   */
  iterator next(size_t dist = 1) const;

  /**
   * @brief Get an iterator in a prev position.
   *
   * @param dist number of prev positions.
   * @return an iterator in a prev position.
   */
  iterator prev(size_t dist = 1) const;

  /**
   * @brief Distance between iterators.
   * Size of the range [this, other)
   * @param other the end of the range
   * @return distance between iterators.
   * @pre this iterator is an before position than other.
   */
  size_t distance(const iterator &other) const;

  /**
   * @brief Is ot iterator in the same position than this?
   */
  bool operator==(iterator const &ot) const;

  /**
   * @brief Is ot iterator in a different position than this?
   */
  bool operator!=(iterator const &ot) const;

  /** @}*/

  /** @name Modifiers.*/
  /** @{*/
  /**
   * @brief Set the item object
   *
   * @param item the value to be set.
   */
  void set_item(const T &item);

  /**
   * @brief move iterator to a next position.
   *
   * @param dist number of next positions.
   */
  void goto_next(size_t dist = 1);

  /**
   * @brief move iterator to a prev position.
   *
   * @param dist number of prev positions.
   */
  void goto_prev(size_t dist = 1);
  /** @}*/

protected:
  friend class List<T>; /**Only a list can create iterators.*/

  /** @name Life cycle.*/
  /** @{*/

  /**
   * @brief Construct a new List Iterator object.
   * The iterator is invalid (points to nothing)
   * @post !is_valid()
   */
  ListIterator();

  /**
   * @brief Construct a new List Iterator points to list node.
   *
   * @param node the node pointed by this iterator.
   */
  ListIterator(typename DNode<T>::Ref const &node);

  /** @}*/

  /**
   * @brief Get the node pointed by this iterator.
   *
   * @return the node pointed by this iterator.
   */
  typename DNode<T>::Ref node() const;

  /**
   * @brief Change the node pointed by this iterator.
   *
   * @param n the node pointed by this iterator.
   */
  void set_node(typename DNode<T>::Ref const &n);

  // TODO: give a representation.
  typename DNode<T>::Ref node_;
  //
};

/**
 * @brief ADT List.
 * Models a Double linked list[T] with iterators to edit.
 */










template <class T>
class List
{
public:
  /** @brief Define a shared reference to a List.
   * Manages the storage of a pointer, providing a limited garbage-collection
   * facility, possibly sharing that management with other objects.
   * @see http://www.cplusplus.com/reference/memory/shared_ptr/
   */
  typedef std::shared_ptr<List<T>> Ref;

  /** @brief Define an iterator to edit the list.*/
  typedef ListIterator<T> iterator;

  /** @name Life cycle.*/
  /** @{*/

  /** @brief Destroy a List.**/
  ~List();

  /**
   * @brief Create a List using dynamic memory.
   * @return a shared reference to the new slist.
   */
  static typename List<T>::Ref create();

  /**
   * @brief Create a List unfolding from an input stream.
   *
   * The input format will be "[]" for the empty list
   * or "[" item1 item2 ... item_n "]" where item1 is the head.
   *
   * @param in is the input stream.
   * @warning if the input format is not correct a std::runtime_error with
   * what message "Wrong input format." will be raised.
   * @return A shared reference to the new slist.
   */
  static typename List<T>::Ref create(std::istream &in) noexcept(false);

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /**
   * @brief is the list empty?.
   * @return true if it is an empty list.
   */
  bool is_empty() const;

  /** @brief Get the number of items in the list.*/
  size_t size() const;

  /**
   * @brief Get the head item of the list.
   * @return the item at the head.
   * @pre !is_empty()
   */
  T front() const;

  /**
   * @brief Get the back item of the list.
   * @return the item at the back.
   * @pre !is_empty()
   */
  T back() const;

  /**
   * @brief Fold to an output stream.
   *
   * The format will be '[' item1 item2 item3 ... item_n ']'
   * where item1 is the head.
   *
   * @param out is the output stream.
   * @return the output stream.
   */
  void fold(std::ostream &out) const;

  /**
   * @brief Returns an iterator to the beginning.
   *
   * @return an iterator to the beginning.
   */
  iterator begin() const;

  /**
   * @brief Returns an iterator to the end.
   *
   * @return an iterator iterator to the end.
   */
  iterator end() const;

  /**
   * @brief Find an item in the list.
   * If the item is not found, the end iterator will be returned.
   * @param it is the value to be found.
   * @param from is the position from starting to find out.
   * @return an iterator to the first found position or end iterator if it was not found.
   * @post ret_val==end() || ret_val->item()==it
   */
  iterator find(T const &it, iterator const &from = begin()) const;

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief insert a new item before the position.
   * @param pos position in the list where inserting.
   * @param it is the item to insert.
   * @return an iterator points to the new item.
   * @post ret_v->item()==it
   * @post !old.is_empty() || (front()==it && back()==it)
   * @post old.is_empty() || ret_v->next()==pos
   * @post old.is_empty() || old.pos->prev()==ret_v->prev()
   * @post size()==(old.size()+1)
   */
  iterator insert(iterator const &pos, T const &it);

  /**
   * @brief Remove the item at a given position.
   * @pre pos is in a valid position [begin(), end())
   * @return an interator following the removed item.
   * @pre not is_empty()
   * @post ret_v == old pos->next()
   * @post ret_v->prev() == old pos->prev()
   * @post size()==(old.size()-1)
   */
  iterator remove(iterator const &pos);

  /**
   * @brief insert an item as the new list's head.
   * @param new_it is the item to insert.
   * @post front()==new_it
   * @post size()==(old.size()+1)
   */
  void push_front(T const &new_it);

  /**
   * @brief insert an item as the new list's back.
   * @param new_it is the item to insert.
   * @post front()==new_it
   * @post size()==(old.size()+1)
   */
  void push_back(T const &new_it);

  /**
   * @brief Remove the head.
   * @pre !is_empty()
   * @post is_empty() || begin() == old begin()->next()".
   * @post size()==(old.size()-1)
   */
  void pop_front();

  /**
   * @brief Remove the back.
   * @pre !is_empty()
   * @post is_empty() || end()->prev() == old end()->prev()->prev()
   * @post size()==(old.size()-1)
   */
  void pop_back();

  /**
   * @brief Transfers elements from one list'range [first, last) to this list.
   *
   * No elements are copied or moved, only the internal pointers of the list
   * nodes are re-pointed. No iterators or references become invalidated,
   * the iterators to moved elements remain valid, but now refer into *this,
   * not into other.
   *
   * @param pos postion of this where transferring the nodes.
   * @param list2 the list from the nodes are transferred
   * @param first fist position of the range.
   * @param last last position of the range.
   */
  void splice(iterator const &pos, Ref list2,
              iterator const &first, iterator const &last);
  /**
   * @brief Transfers all elements from one list to this list.
   *
   * No elements are copied or moved, only the internal pointers of the list
   * nodes are re-pointed. No iterators or references become invalidated,
   * the iterators to moved elements remain valid, but now refer into *this,
   * not into other.
   *
   * @param pos postion of this where transferring the nodes.
   * @param list2 the list from the nodes are transferred.
   */
  void splice(iterator const &pos, Ref list2);

  /**
   * @brief Transfers one element from one list to this list.
   *
   * No elements are copied or moved, only the internal pointers of the list
   * nodes are re-pointed. No iterators or references become invalidated,
   * the iterators to moved elements remain valid, but now refer into *this,
   * not into other.
   *
   * @param pos position of this where transferring the nodes.
   * @param list2 the list from the nodes are transferred.
   * @param i position of the element to be transferred.
   */
  void splice(iterator const &pos, Ref list2, iterator const &i);

  /**
   * @brief merges other into this list.
   *
   * Both lists should be sorted. No elements are copied, and the container
   * other becomes empty after the merge.
   *
   * @tparam Compare comparison function object which returns ​true if the first argument is ordered before the second.
   *
   * The signature of the comparison function should be equivalent to
   * the following: bool cmp(const Type1& a, const Type2& b);
   *
   * @param other the list to be merged with this list.
   * @param cmp comparison object.
   */
  template <class Compare>
  void merge(List<T>::Ref other, Compare cmp);

  /**
   * @brief Sorts the elements of the list.
   *
   * @tparam Compare comparison function object which returns ​true if the first argument is ordered before the second.
   *
   * The signature of the comparison function should be equivalent to
   * the following: bool cmp(const Type1& a, const Type2& b);
   *
   * @param cmp comparison object.
   *
   * @post time analysis: O(N Log N)
   */
  template <class Compare>
  void sort(Compare cmp);

  /** @}*/

protected:
  /** @brief Create an empty List.
   * We make this private to assure that dynamic references are created only.
   * @post is_empty()
   */
  List();

  /**
   * @brief Hook a node to this list before pos.
   *
   * @param n the node to be hooked
   * @param pos the position where hooking the node.
   * @post size()=old.size()+1
   */
  void hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos);

  /**
   * @brief Unhook a node from the list.
   *
   * @param n the node to be unhooked.
   * @post size()==old.size()-1
   */
  void unhook(typename DNode<T>::Ref pos);

  /**
   * @brief Get a reference to the dummy node.
   * The dummy node mark the "end" of the sequence and its linked with the
   * the head and the back of the list.
   * @return a reference to the head node.
   */
  typename DNode<T>::Ref dummy() const;

  /**
   * @brief Set the size of the list.
   */
  void set_size(size_t new_size);

  /**
   * @brief Gets a self reference to this.
   *
   * @return a self reference to this.
   */
  Ref This() const { return this_; }
  Ref this_; /*hold a self reference to this.*/

  // TODO
  // Give a representation using a double linked list of nodes thats used
  // a dummy node to mark the "end" of the list.
  // Also we want a size() operation with O(1).

  //

  typename DNode<T>::Ref _dummy;
  size_t _size;
};

#include "list_imp.hpp"