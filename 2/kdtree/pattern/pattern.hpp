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
#include <exception>
#include <valarray>
#include <vector>
#include <functional>
#include <memory>
#include <exception>

/**
 * @brief ADT Pattern.
 * Models a pattern for Machine Learning.
 */
class Pattern
{
public:
    /**
     * @brief Type for functions that compute distances between patterns.
     *
     */
    typedef std::function<float(const Pattern &a, const Pattern &b)> distance_function_t;

    /**
     * @brief Define a shared reference to a Pattern.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr<Pattern> Ref;

    /** @name Life cycle.*/

    /** @{*/

    /** 
     * @brief Create a pattern.
     * @pre d>=0
     * @post dim()==d
     * @post class_label()==cl
     * @warning by default d=0 but you cat set it properly later.
     */
    Pattern(size_t d = 0, int cl = -1);

    /** 
     * @brief Create a pattern.
     * @pre size>0
     * @post dim()==size
     * @post class_label()==cl
     */
    Pattern(const float values[], const size_t size, const int cl = -1);

    /**
     * @brief Create a pattern.
     * @post dim()==values.size()
     * @post class_label()==cl
     */
    Pattern(const std::vector<float> &values, const int cl = -1);

    /**
     * @brief Create a pattern.
     * @post dim()==values.size()
     * @post class_label()==cl
     */
    Pattern(const std::valarray<float> &values, const int cl = -1);

    /**
     * @brief Create a pattern unfolding from an intput stream.
     * Input format: [ <class_label> [ <dim_0> ... <dim_n-1> ] ]
     * @param in is the input stream.
     * @warning std::runtime_error("wrong input format") was throw if an error happened.
     */
    Pattern(std::istream& in) noexcept(false);
    
    /** @brief Destroy a pattern.**/
    ~Pattern();

    /** @}*/

    /** @name Observers*/

    /**@{*/

    /** 
     * @brief get the pattern's dimension.
     */
    size_t dim() const;

    /** 
     * @brief get the class label
     */
    int class_label() const;

    /**
     * @brief Equality comparison between patterns.
     * 
     * @param o the other pattern.
     * @return true if class_label()==o.class_label() && 
     *         dim()==o.dim() && (this-o).sum()==0.0     
     */
    bool operator==(const Pattern& o);

    /** 
     * @brief get the n-dimension
     * @pre 0<= idx < dimensions()
     */
    float operator[](const size_t idx) const;

    /** 
     * @brief get the sum of all values.
     */
    float sum() const;

    /** 
     * @brief get the maximum of all values.
     * @post retVal >= all values.
     */
    float max() const;

    /** 
     * @brief get the minimum of all values.
     * @post retVal <= all values.
     */
    float min() const;

    /**
     * @brief Return a deep copy of this.     * 
     * @return a copy of this.
     */
    Pattern copy() const;

    /**
     * @brief Fold a pattern into the output stream.
     * Format: [ class_label [ v0 v1 v2 .. vn-1 ] ]
     * @param out the output stream.
     * @return std::ostream& 
     */
    std::ostream& fold (std::ostream& out) const;

    /**
     * @brief Get the values of the pattern dimensions.
     * 
     * @return the values.
     */
    std::valarray<float> values () const;

    /**@}*/

    /** @name Modifiers*/

    /** @{*/

    /** 
     * @brief set pattern's dimension resizing the pattern.
     * @post dim()==dim.
     */
    void set_dim(size_t new_dim);

    /** 
     * @brief set the class label.
     * @post class_label() == new_label
     */
    void set_class_label(const int new_label);

    /**
     * @brief Set i-n dimension value.
     * @pre 0<=idx<dim()
     * @post (*this)[idx]==new_val
     */
    void set_value(size_t idx, const float new_val);

    /**
     * @brief add other pattern to this.
     * @return a reference to updated this.
     * @pre dim()==other.dim()
     * @post this == (old.this()+other)
     */
    Pattern &operator+=(const Pattern &other);

    /** 
     * @brief Subtract other pattern to this.
     * @return a reference to updated this.
     * @pre dim()==other.dim()
     * @post this == (old.this()-other)
     */
    Pattern &operator-=(const Pattern &other);

    /** 
     * @brief elementwise product.
     * @return a reference to updated this.
     * @pre dim()==other.dim()
     * @post this == (old.this()*other)
     */
    Pattern &operator*=(const Pattern &other);

    /** 
     * @brief elementwise division.
     * @return a reference to updated this.
     * @pre dim()==other.dim()
     * @post this == (old.this()/other)
     */
    Pattern &operator/=(const Pattern &other);

    /** 
     * @brief multiply each element by a constant value.
     * @return a reference to updated this.
     * @post for each dimension i, This[i] = old.This[i]*c
     */
    Pattern &operator*=(const float c);

    /** 
     * @brief divide each element by a constant value.
     * @return a reference to updated this.
     * @post for each dimension i, this[i] = old.this[i]/c
     */
    Pattern &operator/=(const float c);

    /**
     * @brief apply absolute value for all dimensions.
     * @return a reference to updated this.
     * @post for each dimension i, (*this)[i] == abs( (* old.this)[i])     *      
     */
    Pattern& abs();

    /** @} */

protected:
    // TODO: Think about a representation.
    int _class_label;
    std::shared_ptr<std::valarray<float>> _values;
    //
};

/** @brief add two patterns.
 *  @pre a.dim()==b.dim()
 */
inline Pattern
operator+(const Pattern &a, const Pattern& b)
{
    Pattern ret = a.copy();
    ret += b;
    return ret;
}

/** @brief Subtract two patterns.
 *  @pre a.dim()==b.dim()
 */
inline Pattern
operator-(const Pattern &a, const Pattern& b)
{
    Pattern ret= a.copy();
    ret -= b;
    return ret;
}

/** @brief multiply (elementwise) two patterns.
 *  @pre a.dim()==b.dim()
 */
inline Pattern
operator*(const Pattern &a, const Pattern& b)
{
    Pattern ret= a.copy();
    ret *= b;
    return ret;
}

/** @brief divide (elementwise) two patterns.
 *  @pre a.dim()==b.dim()
 */
inline Pattern
operator/(const Pattern &a, const Pattern& b)
{
    Pattern ret= a.copy();
    ret /= b;
    return ret;
}

/** @brief multiply by a constant all the dimensions of a pattern.*/
inline Pattern
operator*(const Pattern &a, const float c)
{
    Pattern ret= a.copy();
    ret *= c;
    return ret;
}

/** @brief divide by a constant all the dimensions of a pattern.*/
inline Pattern
operator/(const Pattern &a, const float c)
{
    Pattern ret= a.copy();
    ret /= c;
    return ret;
}

/** @brief multiply by a constant all the dimensions of a pattern.*/
inline Pattern
operator*(const float c, const Pattern &a)
{
    Pattern ret= a.copy();
    ret *= c;
    return ret;
}

/** @brief scalar product of two patterns.
    @pre a.dim()==b.dim()
*/
inline float
dot(const Pattern &a, const Pattern &b)
{
    return (a * b).sum();
}

/**
 * @brief Euclidean distance between patterns.
 * 
 * @param a one pattern
 * @param b other pattern
 * @return euclidean distance for a and b.
 * @post ret_val>=0.0
 */
float distance_L2(const Pattern& a, const Pattern& b);

/**
 * @brief Manhattan distance between patterns.
 * 
 * @param a one pattern
 * @param b other pattern
 * @return manhattan distance for a and b.
 * @post ret_val>=0.0
 */
float distance_L1(const Pattern& a, const Pattern& b);

/** 
 * @brief Load a pattern from an input stream.
 * @pre the input format will be "class_label d0 ... dn-1"
 */
std::istream &operator>>(std::istream &input, Pattern &p) noexcept(false);

/** 
 * @brief Output a pattern to an output stream.
 * @post the output format will be "class_label d0 ... dn-1\n"
 */
std::ostream &operator<<(std::ostream &output, const Pattern &p);

/** 
 * @brief Load a file with patterns.
 * @pre the format is a first line <size_t num patterns> <size_t dimension> and then
 * a pattern per line.
 * @warning throw runtime_error("wrong format") when wrong input format was detected.
 */
std::istream &load_dataset(std::istream &input,
                           std::vector<Pattern> &dts) noexcept(false);
