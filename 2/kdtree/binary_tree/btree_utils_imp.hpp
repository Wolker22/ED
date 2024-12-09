/**
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
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO

    int left_height = 0;
    int right_height = 0;
    if(t->is_empty()){
        return -1;
    }

    left_height=compute_height<T>(t->left()); //mandar nodo izquierdo
    right_height=compute_height<T>(t->right()); //mandar nodo derecho

        //POR QUE LO DE <T>?????

    if(left_height>=right_height){
        height= 1 + left_height;
     }
    else{
        height = 1 + right_height;
     }

    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.

    int left_size = 0;
    int right_size = 0;
    if(t->is_empty()){
        return 0;
    }

    left_size=compute_size<T>(t->left()); //mandar nodo izquierdo
    right_size=compute_size<T>(t->right()); //mandar nodo derecho

    ret_val = 1 + left_size + right_size;

    //
    return ret_val;
}

















template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.

    if(tree->is_empty()){
        return retVal;
    }

    retVal= retVal && p(tree);
    retVal = retVal && prefix_process<T>(tree->left(), p);

    retVal = retVal && prefix_process<T>(tree->right(), p);

    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.

    if(tree->is_empty()){
        return retVal;
    }


    retVal = retVal && infix_process<T>(tree->left(), p);    
    retVal= retVal && p(tree);
    retVal = retVal && infix_process<T>(tree->right(), p);

    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.

    if(tree->is_empty()){
        return retVal;
    }

    retVal = retVal && postfix_process<T>(tree->left(), p);
    retVal = retVal && postfix_process<T>(tree->right(), p);
    retVal= retVal && p(tree);

    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.

    std::queue<typename BTree<T>::Ref> aux; //usamos una cola siempre

    aux.push(tree);

    while(go_on && !(aux.empty())){

        auto front = aux.front();
        aux.pop();
        if(!front->is_empty()){
            aux.push(front->left());
            aux.push(front->right());
            go_on=p(front);
        }

    }

    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remember: the lambda must return true.

    // Definir una función lambda que imprime el elemento del nodo
    auto printNode = [&out](typename BTree<T>::Ref tree) {
        out << tree->item() << " "; // Imprimir el elemento seguido de un espacio
        return true;        // Continuar el procesamiento
    };

    // Aplicar la función lambda al árbol utilizando un recorrido en pre-fijo
    prefix_process<T>(tree, printNode);

    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.

    // Definir una función lambda que imprime el elemento del nodo
    auto printNode = [&out](typename BTree<T>::Ref tree) {
        out << tree->item() << " "; // Imprimir el elemento seguido de un espacio
        return true;        // Continuar el procesamiento
    };

    // Aplicar la función lambda al árbol utilizando un recorrido en infijo
    infix_process<T>(tree, printNode);

    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.

    // Definir una función lambda que imprime el elemento del nodo
    auto printNode = [&out](typename BTree<T>::Ref tree) {
        out << tree->item() << " "; // Imprimir el elemento seguido de un espacio
        return true;        // Continuar el procesamiento
    };

    // Aplicar la función lambda al árbol utilizando un recorrido en postfijo
    postfix_process<T>(tree, printNode);

    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.

    // Definir una función lambda que imprime el elemento del nodo
    auto printNode = [&out](typename BTree<T>::Ref tree) {
        out << tree->item() << " "; // Imprimir el elemento seguido de un espacio
        return true;        // Continuar el procesamiento
    };

    // Aplicar la función lambda al árbol utilizando un recorrido en anchura
    breadth_first_process<T>(tree, printNode);

    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.

    auto f = [&it,&count](typename BTree<T>::Ref tree){
        count++;
        if(it != tree->item()){
          return true;  
        }
        return false;
    };

    found = !prefix_process<T>(tree,f);

    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.

    auto f = [&it,&count](typename BTree<T>::Ref tree){
        count++;
        if(it != tree->item()){
          return true;  
        }
        return false;
    };

    found = !infix_process<T>(tree,f);
    
    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.

    auto f = [&it,&count](typename BTree<T>::Ref tree){
        count++;
        if(it != tree->item()){
          return true;  
        }
        return false;
    };

    found = !postfix_process<T>(tree,f);
    
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.

    auto f = [&it,&count](typename BTree<T>::Ref tree){
        count++;
        if(it != tree->item()){
          return true;  
        }
        return false;
    };

    found = !breadth_first_process<T>(tree,f);
    

    //
    return found;
}
























//no se refiere a si es un arbol ordenado en sentido que a la izquierda menores de root y derecha mayores, es en el sentido de que todo nodo será mayor que su predecesor
template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    
    std::shared_ptr<T> prev_val=nullptr;
    auto f = [&](typename BTree<T>::Ref tree){
        if(prev_val == nullptr){ //prev_val está vacio porque es el primer elemento
            prev_val = std::make_shared<T>(tree->item());
            return true;
        }else{//en el resto de casos es este
            if(*prev_val < tree->item()){//si el valor en prev, es menor que el actual todo bien, y se actualiza el prev
                *prev_val = tree->item();
                return true;
            }
            return false;//en caso que no, se retorna false, y es que no está en orden
        }
    };

    ret_val = infix_process<T>(tree,f);

    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO

    if(tree->is_empty()){
        return ret_val;
    }

    if(tree->item() == v){
        ret_val = true;
    }else{
        if(v < tree->item()){
           ret_val = has_in_order<T>(tree->left(),v);
        }else{
            ret_val = has_in_order<T>(tree->right(),v);
        }
    }

    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO

    if(tree->is_empty()){
        tree->create_root(v);
        return;
    }

    if(tree->item() == v){
        return;
    }
    
    if(v < tree->item()){
        if(tree->left()->is_empty()){
            tree->set_left(BTree<T>::create(v)); // Crear un nuevo nodo y asignarlo al subárbol izquierdo
        }else{
            insert_in_order(tree->left(),v);
        }
    }else{
        if(tree->right()->is_empty()){
            tree->set_right(BTree<T>::create(v)); // Crear un nuevo nodo y asignarlo al subárbol derecho
        }else{
            insert_in_order(tree->right(),v);
        }
    }
   
    //
    assert(has_in_order<T>(tree, v));
}
