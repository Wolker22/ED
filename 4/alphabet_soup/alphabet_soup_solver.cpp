/**
 * @file alphabet_soup_solver.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "alphabet_soup_solver.hpp"
#include "trie.hpp"

/**
 * @brief scan a cell looking for the next letter of a word.
 * @param row and
 * @param col are the current cell coordinates.
 * @param dy and
 * @param dx are direction vector to follow the next letter.
 * @param soup is the alphabet soup where looking for.
 * @param trie is the current subtrie.
 * @param scan_result save the current chain. Is a pair of <word, cells_coordinates [row,col]>
 *
 */
void scan_cell(int row, int col, int dy, int dx, AlphabetSoup const &soup,
               Trie &trie, ScanResult &scan_result)
{
    // TODO
    // ALGORITHM
    // 1. If the trie's prefix is a key then
    //    a word is found. Save the key as the first item of the scan_result
    //    pair and return from this level of recursion.
    // 2. Else if there is a sub-trie for the symbol (row,col), there is two cases:
    // 2.1.1 (dx==dy==0) The cell (row,col) is the first letter of a word.
    //       If there is a sub-trie whose prefix is this symbol, start a new
    //       recursive scanning of the 3x3 neighborhood from this position
    //       using this sub-trie.
    // 2.1.2 (dx!=0 or dy!=0) The cell (row,col) is the next letter of a
    //       started scanning following the direction (dx,dy). If there is a
    //       sub-trie whose prefix is this symbol, continue the scanning
    //       following the direction (dx,dy) recursively.
    // 2.2 After recursion comes back, if a word was found (first item of
    //     the scan_result pair != ""), push the current cell's coordinates
    //     (row,col) into the second item of scan_result (the stack of
    //     coordinates).

    if(trie.is_key()){
        scan_result.first = trie.prefix();
        return;
    }

    if(row < 0 || col < 0 || col >= soup.cols() || row >= soup.rows()){ //comprobamos en el caso de que nos salgamos fuera de la sopa de letras
        return; 
    }

    if(trie.find_symbol(soup.cell(row,col))){ //busca dentro del arbol la letra que esta dentro de la casilla.
        auto souptrie = trie.current();//para obterner el arbol al que esta apuntando y que contiene esa letra
        if(dx == 0 && dy == 0){ // si ambas son cero es que estamos en la primera letra
            for(dy = -1;dy <= 1; dy++){ // vamos a recorrerlo como si fura una matriz con los dos bucles for anidados
                for(dx = -1;dx <= 1; dx++){
                    if(dx != 0 || dy != 0){ // si alguno de los dos es distinto de 0 no sdice que no nos encontramos en el origen
                        scan_cell(row+dy,col+dx,dy,dx,soup,souptrie,scan_result); //llamada recursiva
                        if(scan_result.first != ""){ //evitamos que siga mirando el bucle for en el caso de que aparezca otra vez la letra que estamos buscando 
                        //por ejemplpo en el apalabra Hola que haya dos o cerca
                            scan_result.second.push({row,col});
                            return;
                        }
                    }
                }
            }

        }else{ //ya hemos encontrado la primera fila y ya sabemos cual es la direccion
            scan_cell(row+dy,col+dx,dy,dx,soup,souptrie,scan_result);//llamada recursiva
        }

        if(scan_result.first != ""){
            scan_result.second.push({row,col});
        }       
    }

    //
}

std::vector<ScanResult>
alphabet_soup_solver(AlphabetSoup &soup, std::vector<std::string> const &words)
{
    std::vector<ScanResult> results;
    Trie trie;

    // Generate a trie with the words to be found as keys.
    for (size_t i = 0; i < words.size(); ++i)
        trie.insert(words[i]);

    // We scan all the soup to find a first letter of any key.
    for (int row = 0; row < soup.rows(); ++row)
    {
        for (int col = 0; col < soup.cols(); ++col)
        {
            auto scan_result = std::make_pair(std::string(""),
                                              std::stack<std::pair<int, int>>());
            // Scan from this cell. This is the first letter so dx==dy==0.
            scan_cell(row, col, 0, 0, soup, trie, scan_result);
            if (scan_result.first != "")
                // A word was found so save it into the results.
                results.push_back(scan_result);
        }
    }
    return results;
}
