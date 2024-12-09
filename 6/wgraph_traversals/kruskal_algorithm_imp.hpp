/**
 * @file kruskal_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <exception>
#include <limits>
#include <memory>
#include <algorithm>

#include "disjointsets.hpp"
#include "kruskal_algorithm.hpp"

// Plantilla de la función para aplicar el algoritmo de Kruskal en un grafo
template <class T>
float kruskal_algorithm(Graph<T, float> &g,
                        std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false)
{
    float total_distance = 0.0; // Inicializamos la distancia total del MST a 0.0

    DisjointSets sets(g.num_vertices()); // Creamos una estructura de conjuntos disjuntos para manejar los nodos

    // Creamos un conjunto separado para cada nodo
    for (size_t i = 0; i < g.num_vertices(); ++i)
        sets.make_set(i);

    auto edges = g.edges(); // Obtenemos todas las aristas del grafo

    // Función de comparación para ordenar las aristas primero por peso y luego lexicográficamente
    auto comp = [](typename Graph<T, float>::EdgeRef &u, typename Graph<T, float>::EdgeRef &v) -> bool
    {
        if (u->item() == v->item()) // Si los pesos son iguales
        {
            if (u->first()->label() == v->first()->label()) // Si el primer nodo es igual
            {
                return (u->second()->label() < v->second()->label()); // Ordenamos por el segundo nodo
            }
            return u->first()->label() < v->first()->label(); // Ordenamos por el primer nodo
        }
        return u->item() < v->item(); // Ordenamos por peso
    };

    // Ordenamos las aristas usando la función de comparación
    std::sort(edges.begin(), edges.end(), comp);

    // Iteramos sobre las aristas ordenadas hasta que el MST tenga (n-1) aristas
    for (size_t i = 0; i < edges.size() && (mst.size() < (g.num_vertices() - 1)); i++)
    {
        int u_label = edges[i]->first()->label(); // Etiqueta del primer nodo de la arista
        int v_label = edges[i]->second()->label(); // Etiqueta del segundo nodo de la arista

        // Si los nodos no están en el mismo conjunto, los unimos y añadimos la arista al MST
        if (sets.find(u_label) != sets.find(v_label)) 
        {
            sets.joint(u_label, v_label); // Unimos los conjuntos de los dos nodos
            mst.push_back(edges[i]); // Añadimos la arista al MST
            total_distance += edges[i]->item(); // Añadimos el peso de la arista a la distancia total
        }
    }

    return total_distance; // Devolvemos la distancia total del MST
}
