/**
 * @file avltree.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <functional>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

/**
 * @brief a AVLTree's Node.
 * Models a node of AVLTree.
 * @invariant height = 1 + max{ left's height, right's height }
 */
template <class T>
class AVLTNode
{
public:
  /** @brief Define a shared reference to a AVLTNode.
   * Manages the storage of a pointer, providing a limited garbage-collection
   * facility, possibly sharing that management with other objects.
   * @see http://www.cplusplus.com/reference/memory/shared_ptr/
   */
  typedef std::shared_ptr<AVLTNode<T>> Ref;

  /** @name Life cicle.*/
  /** @{*/

  /**
   * @brief Create a AVLTNode as a leaf node.
   * @param it is the node's item value.
   * @return a shared reference to node created.
   * @post parent()==nullptr
   * @post left()==nullptr
   * @post height()==nullptr
   */
  AVLTNode(T const &it);

  /**
   * @brief Create a AVLTNode as a leaf node.
   * @param it is the node's item value.
   * @return a shared reference to node created.
   * @post parent()==nullptr
   * @post left()==nullptr
   * @post height()==nullptr
   */
  static typename AVLTNode<T>::Ref create(T const &it);

  /**
   * @brief Create a AVLTNode.
   * @param it is the node's item value.
   * @param parent is a link to the parent node of this.
   * @param left is a link to the left child node.
   * @param right is a link to the right child node.
   * @return a shared reference to node created.
   */
  AVLTNode(T const &it, AVLTNode<T>::Ref parent,
           AVLTNode<T>::Ref left, AVLTNode<T>::Ref right);

  /**
   * @brief Create a AVLTNode.
   * @param it is the node's item value.
   * @param parent is a link to the parent node of this.
   * @param left is a link to the left child node.
   * @param right is a link to the right child node.
   * @return a shared reference to node created.
   */
  static typename AVLTNode<T>::Ref create(T const &it,
                                          AVLTNode<T>::Ref parent,
                                          AVLTNode<T>::Ref left,
                                          AVLTNode<T>::Ref right);
  /** @brief Destroy a AVLTNode. **/
  ~AVLTNode()
  {
  }

  /** @}*/

  /** @name Observers.*/
  /** @{*/

  /** @brief Get the data item.*/
  T item() const;

  /**
   * @brief Get the node's height.
   * @post time analysis: O(1).
   */
  int height() const;

  /**
   * @brief Get the balance factor of the node.
   * @post time analysis: O(1).
   */
  int balance_factor() const;

  /** @brief get the parent.*/
  AVLTNode<T>::Ref parent() const;

  /** @brief Get a child.
   * @param dir is the direction 0: left, 1:right.
   * @pre dir==0 || dir==1
   */
  AVLTNode<T>::Ref child(int dir) const;

  /** @brief get the left child.
   * @post ret_v == child(0)
   */
  AVLTNode<T>::Ref left() const;

  /** @brief get the right child.
   * @post ret_v == child(1)
   */
  AVLTNode<T>::Ref right() const;

  /** @}*/

  /** @name Modifiers.*/
  /** @{*/

  /**
   * @brief Set the data item.
   * @post item() == new_it
   */
  void set_item(const T &new_it);

  /**
   * @brief Set the parent.
   * @post parent()==new_parent
   */
  void set_parent(Ref new_parent);

  /** @brief set a child.
   * @param dir is the direction 0: left, 1:right.
   * @pre dir==0 || dir==1
   * @post dir==0 || right()==new_child
   * @post dir==1 || left()==new_child
   */
  void set_child(int dir, AVLTNode<T>::Ref new_child);

  /**
   * @brief Set the left child.
   * @post left()==new_child
   */
  void set_left(AVLTNode<T>::Ref new_child);

  /**
   * @brief Set the right child.
   * @post right()==new_child
   */
  void set_right(Ref new_child);

  /**
   * @brief Update node's height.
   * @post Time analysis: O(1)
   */
  void update_height();

protected:
  /**
   * @brief Check the AVLTNode invariant.
   * @return true if height() == 1 + max{ left's height, right's height }
   */
  bool check_height_invariant() const;

  // TODO
  AVLTNode<T>::Ref _left;
  AVLTNode<T>::Ref _right;
  AVLTNode<T>::Ref _parent;
  T _item;
  size_t _height;
  // Give a representation.

  //
};
















































/**
 * @brief ADT AVLTree.
 * A AVLTree is a binary tree that meets the next two invariants:
 * is_a_binary_search_tree()
 * is_a_balanced_tree()
 */
template <class T>
class AVLTree
{
public:
  /** @name Life cicle.*/
  /** @{*/

  /**
   * @brief Create an empty AVLTree.
   * @post is_empty()
   */
  AVLTree();

  /**
   * @brief Create a leaf tree.
   * @post !is_empty()
   */
  AVLTree(T const &item);

  /**
   * @brief Unfold an AVLTree from an input stream.
   * The input format will be:
   * '[]' for the empty tree.
   * '[ '<item>' '<left-subtree>' '<right-subtree>' ]'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param in is the input stream.
   * @param parent is the parent node of the node to be unfolded.
   * @return The node unfolded on success.
   * @warning std::runtime_error("Wrong input format"),
   * std::runtime_error("It is not a binary search tree") or
   * std::runtime_error("It is not an avl bstree") will throw if an error
   * happened.
   */
  AVLTree(std::istream &in) noexcept(false);

  /** @brief Destroy a AVLTree.**/
  ~AVLTree()
  {
  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty() const;

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T item() const;

  /**
   * @brief Fold an AVLTree into an output stream.
   *  * The output format will be:
   * [ <item> <left> <right> ] or [] if it is a empty tree.
   * @param out is the output stream.
   * @return the output stream.
   */
  std::ostream &fold(std::ostream &out) const;

  /** @brief Is the cursor at a valid position?*/
  bool current_exists() const;

  /**
   * @brief Get the current's item.
   * @return The item save in current node.
   * @pre current_exist()
   */
  T current() const;

  /**
   * @brief Computes the current's level (depth) in the tree.
   * @return the level (depth) of current in the tree.
   * @pre current_exist()
   * @post Time analysis: O(N)
   */
  int current_level() const;

  /**
   * @brief Get the left subtree.
   * @pre !is_empty()
   */
  AVLTree<T> left() const;

  /**
   * @brief Get the right subtree.
   * @pre !is_empty()
   */
  AVLTree<T> right() const;

  /**
   * @brief Return the number of keys stored in the tree.
   * @return the tree's size.
   */
  int size() const;

  /**
   * @brief Return the tree's height.
   * @return the tree's height.
   * @post Time analysis: O(1)
   */
  int height() const;

  /**
   * @brief Get balance factor of the tree.
   * @return the tree's balanced factor.
   * @post Time analysis: O(1)
   */
  int balance_factor() const;

  /**
   * @brief Has the tree this key?
   * @post !is_empty() || has==false;
   * @post !old.current_exists() || old.current()==current()
   */
  bool has(const T &k) const;

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief Create the Root node.
   * @param item is value of the root's item.
   * @pre is_empty()
   * @post !is_empty()
   * @post item()==item
   */
  void create_root(T const &item);

  /**
   * @brief Search a key moving the cursor.
   * @post search==false || current()==k
   * @post search==true || !current_exits()
   */
  bool search(T const &k);

  /**
   * @brief Insert a new key in the tree.
   * @warning if k is already in the tree, only it is updated.
   * @post current_exists()
   * @post current()==k
   */
  void insert(T const &k);

  /**
   * @brief remove current from the tree.
   * @pre current_exists()
   * @post not current_exists()
   */
  void remove();

  /** @}*/

protected:
  /**
   * @brief Check the binary search tree invariant.
   * @return true if in-order traversal follow an ordered key sequence.
   * @post Time Analysis: O(N)
   */
  bool is_a_binary_search_tree() const;

  /**
   * @brief Check the balanced tree invariant.
   * A tree is balanced is empty or the left and right subtrees are balanced and
   * its balance factor is in {-1,0,1}.
   * @return true if left and right trees are balanced and this tree is balanced.
   */
  bool is_a_balanced_tree() const;

  /** @brief Create a AVLTree using a given node as root.*/
  AVLTree(typename AVLTNode<T>::Ref const &root_node);

  /**
   * @brief Attach a new subtree as left child.
   * @param subtree is the tree to be attached.
   * @post (subtree.is_empty() || left().item() == subtree.item())
   * @post (!subtree.is_empty() || left().is_empty())
   * @warning this method does not check invariants.
   */
  void set_left(AVLTree<T> &subtree);

  /**
   * @brief Attach a new subtree as right child.
   * @param subtree is the tree to be attached.
   * @post (subtree.is_empty() || right().item() == subtree.item())
   * @post (!subtree.is_empty() || right().is_empty())
   * @warning this method does not check invariants.
   */
  void set_right(AVLTree<T> &subtree);

  /**
   * @brief find the sucessor in order of current.
   * @pre current_exist()
   * @post current_exist() && !current_->has_left()
   * @post current()>old.current()
   */
  void find_inorder_sucessor();

  /**
   * @brief rotate to re-balanced a subtree.
   *
   * Rotate left (@a dir == 0)
   *
   *               P      ->    S
   *              / \          / \
   *             N   S        P   D
   *                /  \     / \
   *               C    D   N   C
   *
   * Rotate right (@a dir == 1)
   *
   *               P      ->    S
   *              / \          / \
   *             S   N        D   P
   *           /  \              / \
   *          D    C            C   N
   *
   * @param P is the root node of the subtree.
   * @param dir is the direction (0->left, 1->right) to rotate.
   * @return S, the new root node of the rotated subtree.
   * @pre P!=nullptr
   * @pre dir in {0,1}
   * @pre S==P->child(1-dir) != nullptr
   */
  typename AVLTNode<T>::Ref rotate(typename AVLTNode<T>::Ref P, int dir);

  /**
   * @brief make a balanced tree.
   * Process from parent_ going up to the root.
   */
  void make_balanced();

  /**
   * @brief get the root node.
   * @return the root node.
   */
  typename AVLTNode<T>::Ref root_node() const;

  /**
   * @brief set the root node.
   * @post new_root == root_node()
   */
  void set_root_node(typename AVLTNode<T>::Ref const &new_root);

  /**
   * @brief get the current node.
   * @return the current node.
   */
  typename AVLTNode<T>::Ref current_node() const;

  /**
   * @brief Set the current node object
   *
   * @param new_c the new current node.
   */
  void set_current_node(typename AVLTNode<T>::Ref const &new_c);

  /**
   * @brief get the parent node.
   * @return the parent node.
   */
  typename AVLTNode<T>::Ref parent_node() const;

  /**
   * @brief Set the parent node object
   *
   * @param new_p the new parent.
   */
  void set_parent_node(typename AVLTNode<T>::Ref const &new_p);

  /**
   * @brief Check the chains from leaf nodes to the root node.
   */
  bool check_parent_chains() const;

  // TODO
  typename AVLTNode<T>::Ref _root;
  typename AVLTNode<T>::Ref _parent;
  typename AVLTNode<T>::Ref _current;
  // Give a representation.

  //
};

#ifdef __ONLY_BSTREE__
/**
 * @brief create a perfectly balanced BSTree.
 * @param data are the keys to be stored.
 * @return the created tree.
 * @pre data.size()>0
 * @post for each subtree: |right()->size() - left()->size()|<=1
 */
template <class T>
AVLTree<T> create_perfectly_balanced_bstree(std::vector<T> &data);
#endif //__ONLY_BSTREE__

#include "avltree_imp.hpp"