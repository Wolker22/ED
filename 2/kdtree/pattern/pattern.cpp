/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "pattern.hpp"

Pattern::Pattern(const size_t d, const int cl)
{
    // TODO

    _class_label = cl;
    _values= std::make_shared<std::valarray<float>>(d);

    //
    assert(dim() == d);
    assert(class_label() == cl);
}

Pattern::Pattern(const float values[], const size_t size, const int cl)
{
    assert(size>0);
    // TODO

    _class_label = cl;
    _values= std::make_shared<std::valarray<float>>(values,size);


    assert(dim() == size);
    assert(class_label() == cl);
}

Pattern::Pattern(const std::vector<float>& values, const int cl)
{
    assert(values.size()>0);
    // TODO

    _class_label = cl;
    _values= std::make_shared<std::valarray<float>>(values.data(),values.size());


    //
    assert(dim() == values.size());
    assert(class_label() == cl);
}

Pattern::Pattern(const std::valarray<float>& values, const int cl)
{
    assert(values.size()>0);
    // TODO

    _class_label = cl;
    _values= std::make_shared<std::valarray<float>>(values);

    //
    assert(dim() == values.size());
    assert(class_label() == cl);
}

std::valarray<float>
Pattern::values () const
{
    std::valarray<float> vs;
    // TODO

    vs=*_values;

    //
    return vs;
}

Pattern Pattern::copy() const
{
    Pattern ret_v;
    // TODO: return a deep copy of this.

    ret_v = Pattern(*(_values), _class_label);

    //
    return ret_v;    
}

Pattern::~Pattern()
{;}

size_t Pattern::dim() const
{
    size_t d = 0;
    // TODO
    d=_values->size();
    //
    return d;
}

bool Pattern::operator==(const Pattern& o)
{
    assert( dim()==o.dim());
    bool ret_val = false;
    // TODO

    if(class_label() == o.class_label()&&(*this-o).abs().sum()==0.0&&dim()==o.dim()){
        ret_val=true;
    }

    //
    assert(!ret_val || class_label() == o.class_label());
    assert(!ret_val || (*this-o).abs().sum()==0.0);
    return ret_val;    
}

void Pattern::set_dim(size_t new_dim)
{
    // TODO
    _values->resize(new_dim);
    //
    assert(dim()==new_dim);
}

int Pattern::class_label() const
{
    int cl = -1;
    // TODO
    return _class_label;
    //
    return cl;
}

float Pattern::operator [](const size_t idx) const
{
    assert(idx < dim());
    float v = 0.0;
    // TODO

    v=(*_values)[idx];

    //
    return v;
}

float Pattern::sum() const
{
    float s = 0.0;
    // TODO

    s=_values->sum();

    //
    return s;
}

float Pattern::max() const
{
    float m = 0.0;
    // TODO

    m=_values->max();
    //
    return m;
}

float Pattern::min() const
{
    float m = 0.0;
    // TODO
    m=_values->min();
    //
    return m;
}

void Pattern::set_class_label(const int new_label)
{
    // TODO
    _class_label=new_label;
    //
    assert (class_label() == new_label);
}

void Pattern::set_value(const size_t idx, const float new_val)
{
    assert(idx < dim());
    // TODO
    (*_values)[idx]=new_val;
    //
    assert((*this)[idx]==new_val);
}

Pattern& Pattern::operator += (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values+=o.values();
        //
    return *this;
}

Pattern& Pattern::operator -= (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values-=o.values();
    //
    return *this;
}

Pattern& Pattern::operator *= (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values*=o.values();
    //
    return *this;
}

Pattern& Pattern::operator /= (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values/=o.values();
    //
    return *this;
}

Pattern& Pattern::operator *= (const float c)
{
    // TODO
    *_values*=c;
    //
    return *this;
}

Pattern& Pattern::operator /= (const float c)
{
    // TODO
    *_values/=c;
    //
    return *this;
} 

Pattern& Pattern::abs()
{
    //TODO
    *_values=std::abs(*_values); //abs devuelve un valrray
    //
    return *this;
}

std::ostream& Pattern::fold(std::ostream& output) const
{
    // TODO
    // Remember: format "[ class_label [ v0 v1 ... vn-1 ] ]"

    output << "[ " << _class_label << " [ ";
    
    // Imprimir los valores
    for (int i = 0; i < _values->size(); ++i) {
        output << (*_values)[i] << " ";
    }
    
    output << "] ]";
    //
    return output;
}

std::ostream& operator << (std::ostream& output, const Pattern& p)
{
    // TODO
    // Hint: use p.fold()

    p.fold(output);

    //
    return output;
}


Pattern::Pattern(std::istream &input) noexcept(false)
{
    // TODO
    // Remember: input format is "[ class_label [ <dim_0> <dim_1> ... <dim_size-1> ] ]"

    std::vector<float> temp;
    std::string token;
    input>>token;
    if(token!="["){
        throw std::runtime_error("Wrong input format.");
    }
    input>>_class_label;
    input>>token;
    if(token!="["){
        throw std::runtime_error("Wrong input format.");
    }
    input >> token;
    while(token!="]"){
        temp.push_back(stof(token));
        input >> token;
    }
    if(!(input>>token)){//esto en un string normal no seria necesario, pero en caso de usar lo con un fichero será necesario para asegurar que no llega al final
        throw std::runtime_error("Wrong input format.");
    }
    if(token!="]"){
        throw std::runtime_error("Wrong input format.");
    }
    _values = std::make_shared<std::valarray<float>>(temp.data(), temp.size());    //
}

std::istream &operator>>(std::istream &input, Pattern &p) noexcept(false)
{
    assert(input);
    p = Pattern(input);
    return input;
}

float
distance_L2(const Pattern& a, const Pattern& b)
{
    float dist = 0.0;
    // TODO
    auto aux=a-b;
    aux*=aux;
    dist=aux.sum();
    dist=std::sqrt(dist);
    //
    assert(dist >= 0.0);    
    return dist;
}

float
distance_L1(const Pattern& a, const Pattern& b)
{
    float dist = 0.0;
    // TODO

    auto aux=a-b;
    aux=aux.abs();
    dist=aux.sum();

    //
    assert(dist >= 0.0);    
    return dist;
}


std::istream&
load_dataset(std::istream& input,
                  std::vector<Pattern>& dts) noexcept(false)
{
    // TODO
    // Remember: input format is
    // "<size_t num_patterns> <size_t pattern_dimensions>
    // <p_0>
    // <p_1>
    // ...
    // <p_num_patterns-1>
    // "

    int num_patterns, pattern_dimension;

    input>>num_patterns>>pattern_dimension;
    dts=std::vector<Pattern>(num_patterns);

    for(int i=0; i<dts.size(); i++){
        input>>dts[i];
        if(dts[i].dim()!=pattern_dimension)
        {
            throw std::runtime_error("Wrong input format.");
        }
    }

    //
    return input;
}
