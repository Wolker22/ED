/**
 * @file avltree_imp.hpp
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

#include "avltree.hpp"

/****
 * AVLTNode class implementation.
 ****/

template <class T>
AVLTNode<T>::AVLTNode(T const &it)
{
    // TODO
    _item=it;
    _parent=nullptr;
    _right=nullptr;
    _left=nullptr;
    _height=0;
    //
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const &it)
{
    return std::make_shared<AVLTNode<T>>(it);
}

template <class T>
AVLTNode<T>::AVLTNode(T const &it, AVLTNode<T>::Ref parent,
                      AVLTNode<T>::Ref left, AVLTNode<T>::Ref right)
{
    // TODO
    _item=it;
    _parent=parent;
    _left=left;
    _right=right;
    update_height();
    //
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const &it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared<AVLTNode<T>>(it, parent, left, right);
}

template <class T>
T AVLTNode<T>::item() const
{
    T value = T();
    // TODO
    value=_item;
    //
    return value;
}

template <class T>
int AVLTNode<T>::height() const
{
    int height = 0;
    // TODO
    height=_height;
    //

    return height;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    // TODO
    int left_height = -1;
    int right_height = -1;
    
    if (left() != nullptr) {
        left_height = left()->height();
    }
    
    if (right() != nullptr) {
        right_height = right()->height();
    }
    
    bf= right_height - left_height;
    //
    return bf;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    AVLTNode<T>::Ref node;
    // TODO
    node=_parent;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::child(int dir) const
{
    assert(dir == 0 || dir == 1);
    AVLTNode<T>::Ref node;
    // TODO
    if(dir==0){
        node=_left;
    }
    else if(dir==1){
        node=_right;
    }

    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    AVLTNode<T>::Ref node;
    // TODO
    node=_left;
    //
    assert(node == child(0));
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    AVLTNode<T>::Ref node;
    // TODO
    node=_right;
    //
    assert(node == child(1));
    return node;
}

template <class T>
bool AVLTNode<T>::check_height_invariant() const
{
    bool ret_val = false;
    // TODO
    int lh=-1;
    int rh=-1;
    if(left()!=nullptr){
        lh=left()->height();
    }
    if(right()!=nullptr){
        rh=right()->height();
    }
    if (height() == std::max(rh, lh) + 1)
    {
        ret_val = true;
    }
    //
    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T &new_it)
{
    // TODO
    _item=new_it;
    //
    assert(item() == new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref new_parent)
{
    // TODO
    _parent=new_parent;
    //
    assert(parent() == new_parent);
}

template <class T>
void AVLTNode<T>::set_child(int dir, Ref new_child)
{
    assert(dir == 0 || dir == 1);
    // TODO
    // Remember to update the height property.
    if(dir==0){
        set_left(new_child);
    }
    else if(dir==1){
        set_right(new_child);
    }
    //
    assert(check_height_invariant());
    assert(dir == 0 || right() == new_child);
    assert(dir == 1 || left() == new_child);
}

template <class T>
void AVLTNode<T>::set_left(Ref new_child)
{
    // TODO
    // Remember to update the height property.
    _left=new_child;
    update_height();
    //
    assert(check_height_invariant());
    assert(left() == new_child);
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref new_child)
{
    // TODO
    // Remember to update the height property.
    _right=new_child;
    update_height();
    //
    assert(check_height_invariant());
    assert(right() == new_child);
}

template <class T>
void AVLTNode<T>::update_height()
{
    // TODO
    // Remember: we want O(1) here.
    int lh=-1;
    int rh=-1;
    if(left()!=nullptr){
        lh=left()->height();
    }
    if(right()!=nullptr){
        rh=right()->height();
    }
    _height=1+std::max(lh, rh);
    //
    assert(check_height_invariant());
}
































/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree()
{
    // TODO

    _root=nullptr;
    _parent=nullptr;
    _current=nullptr;

    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(is_empty());
}

template <class T>
AVLTree<T>::AVLTree(T const &item)
{
    // TODO
    _root=std::make_shared<AVLTNode<T>>(item);
    _parent=nullptr;
    _current=nullptr;

    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
}

template <class T>
AVLTree<T>::AVLTree(std::istream &in) noexcept(false)
{
    // TODO
    std::string token;
    T aux;
    in>>token;    
    if (token == "[")
    {
    in>>aux;

    create_root(aux);
    auto left_tree=AVLTree(in);
    auto right_tree=AVLTree(in);
    set_left(left_tree);
    set_right(right_tree);
    in>>token;
    if(token!="]"){
        throw std::runtime_error("Wrong input format.");
    }
    }
    else if (token != "[]")
    {
        throw std::runtime_error("Wrong input format.");
    }
        

    //

    if (!is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (!is_a_balanced_tree())
        throw std::runtime_error("It is not an avl tree");
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             AVLTree<T> &tree)
{
    assert(begin <= end);
    assert(end <= data.size());
    assert(begin == end || data[begin] <= data[end - 1]);

    // TODO
    if ((end - begin) >= 1)
    {
        //data puede ser un vector ordenado o no
        tree.insert(data[begin + ((end - begin) / 2)]);//se inserta el dato entre el begin y el end, de manera que se insertaran en su nodo correspondiente
        //piensa que si tienes 4 elementos en el vector primero insertamos la primera mitad el elemento medio, este sera el primero nodo izquierdo del raiz
        create_inserting_median(data, begin, (begin + ((end - begin) / 2)), tree);//inserta una mitad de los elementos de data
        create_inserting_median(data, (begin + ((end - begin) / 2)) + 1, end, tree);//inserta la otra mitad de forma recursiva
    }
    
    // Hint: if (end==begin) none thing must be done (it is an empty sub array)
    //  else, insert the median in the tree and (recursively) process
    //  the two sub sequences [begin, median_idx) and [median_idx+1, end)

    //
}

template <class T>
AVLTree<T>
create_perfectly_balanced_bstree(std::vector<T> &data)
{
    AVLTree<T> tree;
    // TODO
    std::sort(data.begin(), data.end());
    create_inserting_median(data, 0, data.size(), tree);

    // Remember: the empty tree is perfectly balanced.
    // Remember: first, an ordered sequence (using < order) of values is needed.
    // Then you should use the above create_inserting_median function
    // on a empty tree to recursively create the perfectly balanced bstree.

    //
    return tree;
}
#endif //__ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty() const
{
    bool empty = true;
    // TODO
    if(_root!=nullptr){
        empty=false;
    }
    //
    return empty;
}

template <class T>
T AVLTree<T>::item() const
{
    assert(!is_empty());
    T value;
    // TODO
    value=_root->item();
    //
    return value;
}

template <class T>
std::ostream &AVLTree<T>::fold(std::ostream &out) const
{
    // TODO
    if(is_empty()){
        out<<"[]";
        return out;
    }
    out<<"[ "<<item()<<" ";
    left().fold(out);
    out<<" ";
    right().fold(out);
    out<<" ]";

    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    bool exists = false;
    // TODO
    if(_current!=nullptr){
        exists=true;
    }
    //
    return exists;
}

template <class T>
T AVLTree<T>::current() const
{
    assert(current_exists());
    T value;
    // TODO
    value=_current->item();
    //
    return value;
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    // TODO
    auto aux = _current->parent();
    while(aux){
        aux = aux->parent();
        level++;
    }
    //
    return level;
}

template <class T>
AVLTree<T> AVLTree<T>::left() const
{
    assert(!is_empty());
    AVLTree<T> subtree;
    // TODO
    subtree = AVLTree<T>(_root->left());
    //
    return subtree;
}

template <class T>
AVLTree<T> AVLTree<T>::right() const
{
    assert(!is_empty());
    AVLTree<T> subtree;
    // TODO
    subtree = AVLTree<T>(_root->right());
    //
    return subtree;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;
    // TODO
    if(is_empty()){
        s = 0;
    }else{
        s = 1 + left->size() + right->size();
    }
    //
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = 0;
    // TODO
    // Remember: we want O(1) here.
    if(is_empty()){
        h = 0;
    }else{
        h = _root->height();
    }
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    // TODO

    bf = _root->balance_factor();

    //
    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif

    bool found = true;

    // TODO
    // Hint: you can reuse the search method for this but in this case you will
    //       need to use "const_cast" to remove constness of "this" and
    //       save/restore the old state of current before returning.

    auto aux=_root;
    found=false;
    while(aux!=nullptr && !found){
        if(k==aux->item()){
            return true;
        }
        else if(k<aux->item()){
            aux=aux->left();
        }
        else if(k>aux->item()){
            aux=aux->right();
        }
    }
    
    //

#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool infix_process(typename AVLTNode<T>::Ref node, Processor &p)
{
    bool retVal = true;
    // TODO
    // Remember: if node is nullptr return true.
    if(node==nullptr){
        return true;
    }
    else{
        retVal=retVal && infix_process<T>(node->left(), p);
        retVal=retVal && p(node);
        retVal=retVal && infix_process<T>(node->right(), p);
    }
    //
    return retVal;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    // TODO
    // Remember: a empty tree is a binary search tree.
    //

    std::shared_ptr<T> v = nullptr;

    auto p = [&](typename AVLTNode<T>::Ref tree){
        if(v == nullptr){
            v = std::make_shared<T>(tree->item());
            return true;
        }else if(*v < tree->item()){
            *v = tree->item();
            return true;
        }else{
            return false;
        }
    };

    is_bst=infix_process<T>(_root, p);

    // Remember: for a non empty binary search tree, the in-fix traversal from
    // the root node must follow an ordered sequence of items.
    //
    // Remember: use a lambda function with signature '(T v) -> bool' to
    //  implement the Processor.
    //

    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;
    // TODO
    // Remember: a empty tree is balanced.
    //
    if (is_empty() == false)
    {
        is_balanced = (std::abs(balance_factor()) <= 1 && left().is_a_balanced_tree() && right().is_a_balanced_tree());
    }

    // Remember: A non empty tree is balanced if both children are balanced
    // and the absolute value of the balance factor of the tree is less or
    // equal to one.

    //
    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const &v)
{
    assert(is_empty());
    // TODO
    _root = std::make_shared<AVLTNode<T>>(v);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == v);
}

template <class T>
bool AVLTree<T>::search(T const &k)
{
    bool found = false;
    // TODO

    _current = _root;
    _parent = nullptr;//esto es para establecer el parent del sub arbol como el nodo padre del root que tiene este arbol
    //se inicia como nullptr porque si k es el root no tiene padre, al fin y al cabo _parent es el padre del current no del root ¿NO?
    while(_current!=nullptr && !found){
        if(k==_current->item()){
            return true;
        }
        else {
            _parent = _current; //entonces si en la posterior current encuentra k pues el padre de ese arbol ha está selecionado
            if(k<_current->item()){
                _current=_current->left();
            }
            else if(k>_current->item()){
                _current=_current->right();
            }
        }
    }

    //
    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const &k)
{
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    // TODO
    // Remember: after inserting you must balance the tree using make_balanced()
    if (!search(k))
    {
        // TODO
        _current = AVLTNode<T>::create(k,_parent,nullptr,nullptr);
        if(_parent == nullptr){
            create_root(k);
            _current=_root;
        }
        else{
            
            if(k < _parent->item()){
                _parent->set_left(_current);
            }else if(k > _parent->item()){
                _parent->set_right(_current);
            }
        }
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    // check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void AVLTree<T>::remove()
{
    // check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    // the invariants only must be checked for the first recursive call.
    // We use a static variable to count the recursion levels.
    // see section "Static variables in a Function" in
    // ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count == 1)
    {
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());
    }
#endif // NDEBUG

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    // TODO
    //  Check which of cases 0,1,2,3 we have (see theorical class slides).
    if(_current->left()==nullptr && _current->right()==nullptr){
        subtree = nullptr;
    }
    else if(_current->right()==nullptr && _current->left()!=nullptr){
        subtree = _current->left();
    }
    else if(_current->right()!=nullptr && _current->left()==nullptr){
        subtree = _current->right();
    }
    else{
        replace_with_subtree = false;
    }
    //

    if (replace_with_subtree)
    {
        // TODO
        // Manage cases 0,1,2
        // Remember: update subtree to parent links too.
        if(!_parent){
            _root = subtree; 
            if(subtree != nullptr){
                subtree->set_parent(nullptr);
            }
        } else if(_current == _parent->left()){
            _parent->set_left(subtree);
        }
        else{
            _parent->set_right(subtree);
        }
        if(subtree != nullptr){
            subtree->set_parent(_parent);
        }
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
        set_current_node(nullptr);
    }
    else
    {
        // TODO
        // Manage case 3.
        auto aux = _current;
        find_inorder_sucessor();
        aux->set_item(_current->item());
        remove();
        //
    }

#ifndef NDEBUG
    // We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count >= 0);
    if (recursion_count == 0)
    {
        // Only check for the last return.
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());

        // Check postconditions.
        assert(!current_exists());
    }
#endif
}

template <class T>
AVLTree<T>::AVLTree(typename AVLTNode<T>::Ref const &root_node)
{
    // TODO
    set_root_node(root_node);
    //
    assert(!current_exists());
}

template <class T>
void AVLTree<T>::set_left(AVLTree<T> &subtree)
{
    assert(!is_empty());
    // TODO
    // Remember to set parent's link of the subtree root to this.
    _root->set_left(subtree.root_node()); //establezco como node izquierdo de mi raiz el nodo raiz del arbol nuevo
    if(!subtree.is_empty()){
        subtree.root_node()->set_parent(_root);//en caso de que mi arbol no este vacio, querre que el nodo raiz del subarbol sepa cual es su padre
        //¿no debería el subtree saber quien es su padre? para algo tenemos _parent no? NO _PARENT ES EL PARENT DEL NODO CURRENT
    }
    //
    assert(subtree.is_empty() || left().item() == subtree.item());
    assert(!subtree.is_empty() || left().is_empty());
}

template <class T>
void AVLTree<T>::set_right(AVLTree<T> &subtree)
{
    assert(!is_empty());
    // TODO
    // Remember to set parent's link of the subtree root to this.
    _root->set_right(subtree.root_node());
    if(!subtree.is_empty()){
        subtree.root_node()->set_parent(_root);
    }
    //
    assert(subtree.is_empty() || right().item() == subtree.item());
    assert(!subtree.is_empty() || right().is_empty());
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::current_node() const
{
    typename AVLTNode<T>::Ref node;
    // TODO
    node=_current;
    //
    return node;
}

template <class T>
void AVLTree<T>::set_current_node(typename AVLTNode<T>::Ref const &new_c)
{
    // TODO
    _current=new_c;
    //
    assert(current_node() == new_c);
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::root_node() const
{
    typename AVLTNode<T>::Ref node;
    // TODO
    node=_root;
    //
    return node;
}

template <class T>
void AVLTree<T>::set_root_node(typename AVLTNode<T>::Ref const &new_root)
{
    // TODO
    _root=new_root;
    //
    assert(root_node() == new_root);
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::parent_node() const
{
    typename AVLTNode<T>::Ref node;
    // TODO
    node=_parent;
    //
    return node;
}

template <class T>
void AVLTree<T>::set_parent_node(typename AVLTNode<T>::Ref const &new_p)
{
    // TODO
    _parent=new_p;
    //
    assert(parent_node() == new_p);
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());

#ifndef NDEBUG
    T old_curr = current();
#endif
    // TODO

    _parent = _current;
    _current = _current->right();

    while(_current->left() != nullptr){
        _parent = _current;
        _current = _current->left();
    }
    //BUSCA DE LOS MAYORES EL MENOR

    //
    assert(current_exists() && current_node()->left() == nullptr);
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::rotate(typename AVLTNode<T>::Ref P, int dir)
{
    assert(P != nullptr);
    assert(dir == 0 || dir == 1);
    assert(P->child(1 - dir) != nullptr);
    auto N = P->child(1 - dir); // the child to promote.
#ifdef __DEBUG__
    if (__DEBUG__ > 1)
        std::clog << "Rotating to " << (dir == 0 ? "left" : "right") << " on key " << P->item() << std::endl;
#endif
    // TODO
    // Remember update links to parents.
    // Hint: you can see wikipedia: https://en.wikipedia.org/wiki/Tree_rotation


//NI IDEA
    auto a = P->parent();
    auto b = N->child(dir);

    P->set_child(1-dir,b);
    N->set_child(dir,P);
    P->set_parent(N);

    if(b){
        b->set_parent(P);
    }

    if(a){
        if(a->left() == P){
            a->set_left(N);
        }else{
            a->set_right(N);
        }
    }else{
        set_root_node(N);
    }

    N->set_parent(a);

    //
    return N;
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    auto P = parent_node(); // the subtree root node.

    while (P)
    {
        // TODO
        // Checks the subtrees balance factors to do rotations if needed.
        // Remember: first update the height of the subtree root node.

//NI IDEA
        P->update_height();
        int bf_P = P->balance_factor();
        if(std::abs(bf_P)>1){
            int dir = 0;
            if(bf_P>0){
                dir = 1;
            }

            auto N = P->child(dir);
            int bf_N = N->balance_factor();

            if((bf_N*bf_P) >= 0){
                P = rotate(P,1-dir);
            }else{
                rotate(N,dir);
                P = rotate(P,1-dir);
            }
        }    

        //

        P = P->parent(); // going up.
    }
    if (current_exists())
        set_parent_node(current_node()->parent());
    assert(!current_exists() || current_node()->parent() == parent_node());
#endif //__ONLY_BSTREE__
}

template <class T>
bool AVLTree<T>::check_parent_chains() const
{
    if (!is_empty())
    {
        std::function<void(typename AVLTNode<T>::Ref, std::vector<T>)> go_down;
        go_down = [&go_down](typename AVLTNode<T>::Ref node, std::vector<T> branch) -> void
        {
            if (node->left() != nullptr || node->right() != nullptr)
            {
                branch.push_back(node->item());
                if (node->left())
                    // go down by the left
                    go_down(node->left(), branch);
                if (node->right())
                    // go down by the right
                    go_down(node->right(), branch);
            }
            else
            {
                // The node is a leaf node, so check the branch
                // to the tree root node.
                typename AVLTNode<T>::Ref parent = node->parent();
                int idx = static_cast<int>(branch.size()) - 1;
                while (node->parent() && idx >= 0)
                {
                    assert(parent->item() == branch[idx]);
                    --idx;
                    parent = parent->parent();
                }
                assert(idx == -1 && parent == nullptr);
            }
        };
        std::vector<T> branch;
        go_down(root_node(), branch);
    }
    return true;
}
