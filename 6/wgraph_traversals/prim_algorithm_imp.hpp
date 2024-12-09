/**
 * @file prim_algorithm_imp.hpp
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

#include "prim_algorithm.hpp"

template <class T>
float prim_algorithm(Graph<T, float> &g,
                     std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false)
{
    assert(g.has_current_vertex());

    float total_distance = 0.0;
    mst.resize(0);

    auto start_vertex = g.current_vertex();

    // Create and initialize auxiliary vectors.
    auto U = g.vertices();
    std::vector<size_t> V(g.num_vertices());
    std::vector<bool> A(g.num_vertices(), false);
    std::vector<float> C(g.num_vertices(), std::numeric_limits<float>::infinity());

    // Find the index 'u' of the start vertex in vector U.
    size_t u = 0;
    while (U[u] != start_vertex)
        ++u;

    // Add the start vertex to the Minimum Spanning Tree with cost 0.
    A[u] = true;
    C[u] = 0.0;

    // TODO
    // Remember: Use auxiliary vectors U, V, A and C.
    // Remember: U vector has the graph's nodes.
    // Remember: We need to find the N-1 edges.
    for (size_t i = 1; i < U.size(); ++i)
    {
        // Update distances to MST for not visited vertex using as predecessor
        // the vertex 'u'.
        for (size_t j = 0; j < U.size(); j++)
        {
            if (!A[j])
            {
                auto e = g.edge(U[u],U[j]);

                if (e != nullptr)
                {
                    if (e->item() < C[j])
                    {
                        C[j] = e->item();
                        V[j] = u;
                    }
                }
            }
        }        
        //

        float least_cost = std::numeric_limits<float>::infinity();
        // Select the next vertex 'u' to add to the MST (with the least cost).
        for (size_t j = 0; j < U.size(); j++)
        {
            if (!A[j] && C[j] < least_cost)
            {
                least_cost = C[j];
                u = j; 
            }
        }
        //

        assert(!A[u]); // u does not belong to the MST yet.

        // if the least cost found is infinite, this means an unconnected graph
        // is being processed. Throw an exception.
        if (least_cost == std::numeric_limits<float>::infinity() )
        {
            throw std::runtime_error("It is an unconnected graph.");
        }
        //

        // Update the total distances, push back the edge found to the MST and
        // add the found vertex to the MST.
        mst.push_back(g.edge(U[u],U[V[u]]));
        A[u] = true;
        total_distance += C[u];
        //
    }
    //

    return total_distance;
}
