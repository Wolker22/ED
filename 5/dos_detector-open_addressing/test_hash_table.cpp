/**
 * @file test_hash_table.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>

#include "ip_utils.hpp"
#include "hash.hpp"
#include "hash_table_imp.hpp"

std::istream &
operator>>(std::istream &in, std::vector<int> &v)
{
    size_t size;
    in >> size;
    if (in)
    {
        v.resize(size);
        for (size_t i = 0; i < size && in; ++i)
            in >> v[i];
    }
    return in;
}

int main(int argc, const char *argv[])
{
    std::srand(0); // Use always the same random seed.
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file(argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        HashTable<IP, int>::Ref hash_table;
        size_t current_idx;
        std::string buffer;
        std::istringstream input;
        while (std::getline(input_file, buffer))
        {
            if (!input_file || buffer == "" || buffer[0] == '#')
                continue;

            input.str(buffer);
            input.clear();
            std::string command;
            input >> command;
            if (!input)
                continue;

            if (command == "create")
            {
                std::uint64_t m, p, a, b;
                input >> m >> p >> a >> b;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                hash_table = std::make_shared<HashTable<IP, int>>(m, ip_to_int, LPHash::create(UHash(m, p, a, b)));
                std::cout << "Created table with size: " << m << std::endl;
            }
            else if (command == "load_factor")
            {
                std::cout << "load factor: " << hash_table->load_factor()
                          << std::endl;
            }
            else if (command == "has")
            {
                IP ip;
                input >> ip;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                std::cout << "Has key '" << ip << "'?: "
                          << (hash_table->has(ip) ? "yes" : "no") << std::endl;
            }
            else if (command == "size")
            {
                std::cout << "Table size: " << hash_table->size() << std::endl;
            }
            else if (command == "insert")
            {
                IP ip;
                int v;
                input >> ip >> v;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                current_idx = hash_table->insert(ip, v);

                std::cout << "Inserted pair <" << ip << ":" << v << ">"
                          << std::endl;
            }
            else if (command == "find")
            {
                IP ip;
                input >> ip;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                current_idx = hash_table->find(ip);
                if (hash_table->entry(current_idx).is_valid())
                    std::cout << "Key '" << ip << "' found." << std::endl;
                else
                    std::cout << "Key '" << ip << "' not found." << std::endl;
            }
            else if (command == "remove")
            {
                std::cout << "Removing key: " << hash_table->entry(current_idx).key()
                          << " ... ";
                hash_table->remove(current_idx);
                std::cout << " ok." << std::endl;
            }
            else if (command == "set_value")
            {
                int v;
                input >> v;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                std::cout << "Setting current value to " << v << " ... ";
                hash_table->entry(current_idx).value() = v;
                std::cout << " ok." << std::endl;
            }
            else if (command == "show")
            {

                std::cout << "Table: [";
                for (size_t idx = 0; idx < hash_table->size(); ++idx)
                {
                    if (hash_table->entry(idx).is_valid())
                        std::cout << hash_table->entry(idx).key() << ':' << hash_table->entry(idx).value() << ' ';
                }
                std::cout << "]" << std::endl;
            }
            else if (command == "is_valid")
            {
                std::cout << "Is valid?: " << (hash_table->entry(current_idx).is_valid() ? "True" : "False") << std::endl;
            }
            else if (command == "get_key")
            {
                if (hash_table->entry(current_idx).is_valid())
                    std::cout << "Current key: '" << hash_table->entry(current_idx).key() << "'." << std::endl;
                else
                    std::cout << "Current key: not a valid position." << std::endl;
            }
            else if (command == "get_value")
            {
                if (hash_table->entry(current_idx).is_valid())
                    std::cout << "Current value: '" << hash_table->entry(current_idx).value() << "'." << std::endl;
                else
                    std::cout << "Current value: not a valid position." << std::endl;
            }
            else
            {
                std::cerr << "Error: unkown command '" << command << "'." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
