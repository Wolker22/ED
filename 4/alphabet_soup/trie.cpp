/**
 * @file trie.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include "trie.hpp"

Trie::Trie()
{
    // TODO
    _root=nullptr;
    _prefix="";
    //
    assert(is_empty());
}

Trie::Trie(TrieNode::Ref root_node, std::string const &pref)
{
    // TODO
    _root = root_node;
    _prefix = pref;
    //
    assert(prefix() == pref);
}

Trie::Trie(std::istream &in) noexcept(false)
{
    // TODO
    std::string token;
    
    // Leer el prefijo
    in >> token;
    if (token != "[") {        
        throw std::runtime_error("Wrong input format.");
    }

    in >> token;
    if(token != "\""){
        throw std::runtime_error("Wrong input format.");
    }

    in >> token;

    _prefix = "";
    while(token != "\""){
        try{
            _prefix += char(std::stoi(token, nullptr, 16));
        }catch(std::invalid_argument&x){
            throw std::runtime_error("Wrong input format");
        }
        
        in >> token;
    }
    _root = TrieNode::create(in);

    // Verificar el token de cierre
    in >> token;
    if (token != "]") {
        throw std::runtime_error("Wrong input format.");
    }
    //
}

bool Trie::is_empty() const
{
    bool ret_v = true;
    // TODO
    if(_root!=nullptr){
        ret_v=false;
    }
    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    // TODO
    ret_val=_prefix;
    //
    return ret_val;
}

void Trie::set_prefix(const std::string &new_p)
{
    // TODO
    _prefix=new_p;
    //
    assert(prefix() == new_p);
}

bool Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    // TODO
    if(_root->is_key()==false){
        ret_val=false;
    }
    //
    return ret_val;
}

TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node;
    // TODO
    node=_root;
    //
    return node;
}

void Trie::set_root(TrieNode::Ref const &new_r)
{
    // TODO
    _root=new_r;
    //
    assert(root() == new_r);
}

bool Trie::has(std::string const &k) const
{
    assert(!is_empty());
    bool found = false;
    // TODO
    // Hint: use find_node() to do this.
    // Remember: The Trie can have a prefix==k but does not store the key k.

    //K NO ES UNA CLAVE COMO LA DE UN MAPA QUE ES SOLO UN CARACTER, ES UNA CLAVE COMPLETA CON SU PREFIJO Y TODO, ES DECIR IS_KEY()

    TrieNode::Ref node = find_node(k);
    if(node!=nullptr && node->is_key()){
        found=true;
    }

    //
    return found;
}

/**
 * @brief Helper function to retrieve the keys.
 *
 * This function does a recursive preorder traversal of the trie's nodes
 * keeping the current prefix and the retrieved keys as functions parameters.
 *
 * @param[in] node is the current node.
 * @param[in] prefix is the current prefix.
 * @param[in,out] keys are the retrieved keys.
 */
static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> &keys)
{
    // TODO
    // Remember: node->is_key() means the prefix is a key too.
    if(node->is_key()){
        keys.push_back(prefix);
    }
    node->goto_first_child();
    while(node->current_exists()){
        preorder_traversal(node->current_node(), prefix+node->current_symbol(), keys);
        node->goto_next_child();
    }
    
    //
}

void Trie::retrieve(std::vector<std::string> &keys) const
{
    assert(!is_empty());
    // TODO
    // Remember add the subtrie's prefix to the retrieve keys.
    preorder_traversal(_root, prefix(), keys);
    //
}

Trie Trie::child(std::string const &postfix) const
{
    assert(!is_empty());
    Trie ret_v;
    // TODO
    // Hint: use find_node() to follow the chain of nodes whose represent postfix.
    auto node = find_node(postfix);

    if(node == nullptr){
        ret_v = Trie();
    }else{
        ret_v = Trie(node,prefix()+postfix);
    }

    //
    assert(ret_v.is_empty() || ret_v.prefix() == (prefix() + postfix));
    return ret_v;
}

bool Trie::current_exists() const
{
    bool ret_val = false;
    // TODO
    if(_root->current_exists()){
        ret_val=true;
    }
    //
    return ret_val;
}

Trie Trie::current() const
{
    assert(current_exists());
    Trie ret_v;
    // TODO
    ret_v=Trie(_root->current_node(), _prefix+_root->current_symbol());
    //
    return ret_v;
}

char Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    // TODO
    if(_root-> current_exists() == true){
        symbol = _root->current_symbol();
    }else{
        symbol = '\0';
    }
    //
    return symbol;
}

void Trie::insert(std::string const &k)
{
    assert(k != "");
    // TODO

    if (is_empty()) {
        _root = TrieNode::create(false); // Inicializamos el nodo raíz si está vacío
    }

    TrieNode::Ref node = _root;
    for (size_t i = 0; i < k.size(); i++) {
        if (node->has(k[i])) {
            node = node->child(k[i]);
        } else {
            auto newNode = TrieNode::create(false);
            node->set_child(k[i], newNode);
            node = newNode;
        }
    }
    node->set_is_key_state(true);
    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const &pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    // TODO
    // Remember: the prefix "" must return the trie's root node.
    // Si el prefijo es la cadena vacía, devolver el nodo raíz
    node = _root;
    int i = 0;

    // Recorrer el árbol Trie basado en el prefijo dado
    while (i < pref.size() && node != nullptr) {
        if (node->has(pref[i])) {
            node = node->child(pref[i]);
            i++;
        } else {
            // Si no hay un hijo que coincida con el siguiente carácter del prefijo, devolver nullptr
            node = nullptr;
            break;
        }
    }

    //
    return node;
}

std::ostream &
Trie::fold(std::ostream &out) const
{
    // TODO
    out << "[ ";
    out << "\" ";
    for (size_t i = 0; i < _prefix.size(); i++) {
        out << std::hex << (uint16_t)_prefix[i] << " ";
    }
    out<<"\" ";
    if (_root != nullptr)
    {
        _root->fold(out);
    }
    out << " ]";
    //
    return out;
}

bool Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    // TODO
    if(_root->find_child(symbol) == true){
        found = true;
    }
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol() == symbol);
    return found;
}

void Trie::goto_first_symbol()
{
    assert(!is_empty());
    // TODO
    _root->goto_first_child();
    //
    assert(!current_exists() ||
           current().prefix() == (prefix() + current_symbol()));
}

void Trie::goto_next_symbol()
{
    assert(current_exists());
    // TODO
    _root->goto_next_child();
    //
}
