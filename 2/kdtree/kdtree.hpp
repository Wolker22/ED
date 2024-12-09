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
#include <vector>
#include <tuple>


#include "btree.hpp"
#include "pattern.hpp"

/**
 * @brief Models a K-Dimensional Tree.
 *
 * A KDTree organizes a k-dimensional vector space by recursive bipartition of
 * each dimension.
 *
 * This tree allows to find the k nearest neighbour with a better complexity
 * than a exhaustive search (in average case).
 *
 */
class KDTree
{
public:
    /** @brief a reference to a kdtree. */
    typedef std::shared_ptr<KDTree> Ref;

    /** @name Life cycle.*/
    /** @{ */

    /**
     * @brief Create an empty kdtree.
     * @post is_empty()
     */
    KDTree();

    /** 
     * @brief Create an empty KDTree given a dataset.
     * @post ret_v->is_empty()
    */
    static Ref create();

    /** @brief Create a KDTree given a dataset.*/
    static Ref create(std::vector<Pattern> &dataset);

    /** 
     * @brief Create a KDTree unfolding from a stream.
     * Format: <k> <tree>
     * @warning throw std::runtime_error("wrong input format")
    */
    static Ref create(std::istream &in) noexcept(false);

    /**
     * @brief Destroy the KDTree object
     *
     */
    ~KDTree();

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /**
     * @brief Is it empty?
     */
    bool is_empty() const;

    /**
     * @brief number of dimensions of the kdtree.
     * @pre !is_empty()
     */
    size_t get_k() const;

    /**
     * @brief Fold the kdtree into an output stream.
     * Format : <k> <tree>
     * @param out is the output stream to use.
     */
    std::ostream& fold(std::ostream &out) const;

    /**
     * @brief find the nearest neighbour from a given pattern.
     * @param p is the pattern to match with.
     * @param dist is used to compute the distance between two patterns
     * @return a tuple with the nearest pattern and the its distance.
     * @pre not is_empty()
     * @pre p.dim() == k()
     */
    std::tuple<float, Pattern> find_nn(Pattern const &p,
                                       const Pattern::distance_function_t &dist) const;

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /**
     * @brief Rebuild the kdtree to fit a new dataset.
     * 
     * @param dts is the new dataset to be fitted.
     * @pre dts.size()>0
     * @pre All patterns in dts has same dimensions.
     * @post get_k()==dts[0].dim()
     * @post !is_empty()
     */
    void fit (std::vector<Pattern>& dts);

    /** @}*/

protected:

    /**
     * @brief Get the underlying binary tree.
     * @return a const tree's reference.
     */
    BTree<Pattern>::Ref btree() const;

    /**
     * @brief Set the underlying binary tree.     
     */
    void set_btree(BTree<Pattern>::Ref btree);
    
    /**
     * @brief Set the number of vspace dimensions.
     */
    void set_k (size_t k);
    
    // TODO: find a representation.
    // Hint: you can use a binary tree to represent a kdtree.
    size_t _k;
    BTree<Pattern>::Ref _tree;
    //
};
