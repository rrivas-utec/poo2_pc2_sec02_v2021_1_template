//
// Created by rudri on 7/13/2021.
//

#ifndef POO2_PC2_SEC02_V2021_1_BINARY_TREE_H
#define POO2_PC2_SEC02_V2021_1_BINARY_TREE_H

#include <memory>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

// Declaración Forward de un Template (No cuenta con implementacion)
template<typename T>
struct node_impl;

// Declaración del nodo como un puntero inteligente,
// utilizando un alias template
template<typename T>
using node = shared_ptr<node_impl<T>>; // node<T> ~~ shared_ptr<node_impl<T>>

template<typename T>
using weak_node = weak_ptr<node_impl<T>>; // weak_node<T> ~~ weak_ptr<node_impl<T>>

template<typename T, typename ...Params>  // make_node<T> ~~ make_shared<node_impl<T>>
node<T> make_node(Params... params) { return make_shared<node_impl<T>>(params...);}

// DEFINIR EL NODE
// Define el node_impl
template<typename T>
struct node_impl {
    // Atributos
    T data {}; // Data
    weak_node<T> parent {};
    node<T> left {};
    node<T> right {};
    // Constructores
    node_impl() = default;
    explicit node_impl(T data): data{data}, parent{}, left{}, right{} {}
};

template<typename T>
class binary_tree {

    // Atributos
    node<T> root{};

    void pre_order_(vector<T>& result, node<T> nd) {
        if (!nd) return;
        result.push_back(nd->data);
        pre_order_(result, nd->left);
        pre_order_(result, nd->right);
    }

    void in_order_(vector<T>& result, node<T> nd) {
        if (!nd) return;
        in_order_(result, nd->left);
        result.push_back(nd->data);
        in_order_(result, nd->right);
    }

    void post_order_(vector<T>& result, node<T> nd) {
        if (!nd) return;
        post_order_(result, nd->left);
        post_order_(result, nd->right);
        result.push_back(nd->data);
    }

    size_t count_nodes_(node<T> nd) {
        if (nd) return 0;
        return 1 + count_nodes_(nd.left) + count_nodes_(nd.right);
    }

    size_t height_(node<T> nd, node<T> rt) {
        size_t result = 0;
        while (nd != rt) {
            nd = nd->parent.lock();
            ++result;
        }
        return result;
    }

public:
    // NO se Implementa el constructor por default

    // Constructor por parámetros
    explicit binary_tree(T data): root{make_node<T>(data)} {}

    // Constructor por copia (SI ES NECESARIO)
//    binary_tree(const binary_tree& other) {
//        // TO DO
//        // Método recursivo de copia
//    }

    // Operador asignación copia
//    binary_tree& operator=(const binary_tree& other) {
//        // TO DO
//        // Método recursivo de copia
//    }

    // Destructor --> NO ES NECESARIO porque la memoria es administrada por el puntero inteligente

    // Gets
    node<T> get_root() { return root; }
    weak_node<T> get_parent(const node<T>& node) { return node->parent; }
    node<T> get_left_child(const node<T>& node) { return node->left; }
    node<T> get_right_child(const node<T>& node) { return node->right; }

    // Sets
    node<T> add_left(const node<T>& node, T data) {
        // Verificar si el nodo tiene hijo izquierdo
        if (!node->left) {
            node->left = make_node<T>(data);
        }
        else {
            auto temp =  make_node<T>(data);
            temp->left = node->left;
            node->left = temp;
            temp->left->parent = temp;
        }
        node->left->parent = node;
        return node->left;
    }
    node<T> add_right(const node<T>& node, T data) {
        if (!node->right) {
            node->right = make_node<T>(data);
        }
        else {
            auto temp = make_node<T>(data);
            temp->right = node->right;
            node->right = temp;
        }
        node->right->parent = node;
        return node->right;
    }

    // BFS
    vector<T> bfs() {
        // un vector y un queue
        vector<T> result;
        queue<node<T>> q;
        // paso # 1
        q.push(root);
        // paso # 2 Verificar que el queue no este vacio
        while(q.empty() == false) {
            // paso # 2.1: Obtengo el valor y grabo en el vector
            auto temp = q.front();
            result.push_back(temp->data);
            // paso # 2.2: Retiro el valor
            q.pop();
            // paso # 2.3: Agrego los hijos
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        return result;
    }

    // BFS
    template <typename UnaryFunction>
    void recorrido_a_nivel(UnaryFunction func) {
        // un queue
        queue<node<T>> q;
        // paso # 1
        q.push(root);
        // paso # 2 Verificar que el queue no este vacio
        while(q.empty() == false) {
            // paso # 2.1: Obtengo el valor y grabo en el vector
            auto temp = q.front();
            func(temp->data); // <----- USO DEL CALLABLE O FUNCTOR
            // paso # 4: Retiro el valor
            q.pop();
            // paso # 5: Agrego los hijos
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }

    vector<T> dfs() {
        // un vector, un stack, un set, un lambda
        vector<T> res;
        stack<node<T>> s;
        unordered_set<node<T>> u;
        auto is_available = [&u](node<T> n) { return u.find(n) == end(u); };

        // 1. Agregar root
        s.push(root);
        // 2. Verificar si el stack no esta vacio
        while(s.empty() == false) {
            // 2.1 Obtengo el valor
            auto temp = s.top();
            u.insert(temp); // No disponible
            // 2.2 Si tiene hijos disponibles
            if (temp->left && is_available(temp->left))
                s.push(temp->left);
            else if (temp->right && is_available(temp->right))
                s.push(temp->right);
            else { // 2.3 Sino tiene hijos disponibles
                s.pop();
                res.push_back(temp->data);
            }
        }
        return res;
    }

    vector<T> dfs_pre() {
        // un vector, un stack, un set, un lambda
        vector<T> res;
        stack<node<T>> s;
        unordered_set<node<T>> u;
        auto is_available = [&u](node<T> n) { return u.find(n) == end(u); };

        // 1. Agregar root
        s.push(root);
        // 2. Verificar si el stack no esta vacio
        while(s.empty() == false) {
            // 2.1 Obtengo el valor
            auto temp = s.top();
            if (is_available(temp)) {
                u.insert(temp); // No disponible
                res.push_back(temp->data);
            }

            // Si tiene hijos disponibles
            if (temp->left && is_available(temp->left))
                s.push(temp->left);
            else if (temp->right && is_available(temp->right))
                s.push(temp->right);
            else { // Sino tiene hijos disponibles
                s.pop();
            }
        }
        return res;
    }

    vector<T> dfs_in() {
        // un vector, un stack, un set, un lambda
        vector<T> res;
        stack<node<T>> s;
        unordered_set<node<T>> u;
        auto is_available = [&u](node<T> n) { return u.find(n) == end(u); };

        // 1. Agregar root
        s.push(root);
        // 2. Verificar si el stack no esta vacio
        while(s.empty() == false) {
            // 2.1 Obtengo el valor
            auto temp = s.top();
            u.insert(temp); // No disponible
            // Si tiene hijos disponibles
            if (temp->left && is_available(temp->left)) {
                s.push(temp->left);
            }
            else if (temp->right && is_available(temp->right)) {
                res.push_back(temp->data);
                s.push(temp->right);
            }
            else { // Sino tiene hijos disponibles
                res.push_back(temp->data);
                s.pop();
            }
        }
        return res;
    }

    vector<T> pre_order() {
        vector<T> result;
        pre_order_(result, root);
        return result;
    }

    vector<T> in_order() {
        vector<T> result;
        in_order_(result, root);
        return result;
    }

    vector<T> post_order() {
        vector<T> result;
        post_order_(result, root);
        return result;
    }

    bool is_complete() {
        if (root) return true;
        queue<node<T>> q;
        q.push(root);
        bool flag = false;
        while (!q.empty()) {
            auto actual = q.front();
            q.pop();
            if (actual->left) {
                if (flag) return false;
                q.push(actual->left);
            } else
                flag = true;
            if (actual->right) {
                if (flag) return false;
                q.push(actual->right);
            } else
                flag = true;
        }
        return true;
    }

    bool is_max_heap() {
        if (!root) return true;
        if (!is_complete()) return false;
        queue<node<T>> q;
        q.push(root);
        while (!q.empty()) {
            auto actual = q.front();
            q.pop();
            if (actual->left) {
                if (actual->data < actual->left->data) return false;
                q.push(actual->left);
            }
            if (actual->right) {
                if (actual->data < actual->right->data) return false;
                q.push(actual->right);
            }
        }
        return true;
    }
    size_t calculate_distance(node<T> origin, node<T> destination) {
        return size_t{};
    }
};

#endif //POO2_PC2_SEC02_V2021_1_BINARY_TREE_H
