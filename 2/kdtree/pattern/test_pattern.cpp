#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "pattern.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file (argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '"
                      << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }

        std::string command;
        std::cout << std::unitbuf;
        std::istringstream input_line;
        std::string line;
        std::vector<Pattern> dts;

        while(std::getline(input_file, line))
        {
            if (line == "" || line[0]=='#')
                continue;

            input_line.clear();
            input_line.str(line);            
            input_line >> command;
            if (! input_line)
                continue;
                
            if (command == "CREATE_PATTERN")
            {
                int cl;
                std::vector<float> values;
                input_line >> cl;
                while (input_line)
                {
                    float v;
                    input_line >> v;
                    if (input_line)
                        values.push_back(v);
                }
                dts.push_back(Pattern(values, cl));
                std::cout << "Created new pattern with idx=" << dts.size()-1 
                          << " with class label: " 
                          << dts.back().class_label() << std::endl;
            }
            else if (command == "CREATE_ZERO_PATTERN")
            {
                int cl;
                size_t dims;
                input_line >> dims >> cl;
                dts.push_back(Pattern(dims, cl));
                std::cout << "Created new zero pattern with idx=" 
                    << dts.size()-1 << " with class label: "
                    << dts.back().class_label() << std::endl;
            }
            else if (command == "CREATE_PATTERN_AS_ALIAS")
            {
                size_t idx;
                input_line >> idx;
                dts.push_back(Pattern());
                dts.back() = dts[idx];
                std::cout << "Created new pattern with idx=" << dts.size()-1 
                          << " as alias of pattern idx=" << idx << std::endl;
            }
            else if (command == "CREATE_PATTERN_AS_COPY")
            {                
                size_t idx;
                input_line >> idx;
                dts.push_back(Pattern());
                dts.back() = dts[idx].copy();
                std::cout << "Created new pattern with idx=" << dts.size()-1 
                          << " as copy of pattern idx=" << idx << std::endl;
            }
            else if (command == "UNFOLD_PATTERN")
            {
                dts.push_back(Pattern(input_line));
                std::cout << "Unfold pattern idx: " << dts.size()-1 
                    << " with class label: "
                    << dts.back().class_label() << std::endl;
            }
            else if (command == "PATTERN_CLASS_LABEL")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] class label: " 
                          << dts[idx].class_label() << std::endl;
            }
            else if (command == "PATTERN_DIM")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] dim: " 
                          << dts[idx].dim() << std::endl;
            }
            else if (command == "PATTERN_VALUE")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "dts[" << idx1 << "][" << idx2 << "] = " 
                          << dts[idx1][idx2] << std::endl;
            }
            else if (command == "FOLD_PATTERN")
            {
                int idx;
                input_line >> idx;
                std::cout << "Fold dts[" << idx << "]: '" << dts[idx] << "'" << std::endl;
            }
            else if (command == "PATTERN_MIN")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] min: '" << dts[idx].min() 
                    << "'" << std::endl;
            }
            else if (command == "PATTERN_MAX")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] max: '" << dts[idx].max() 
                    << "'" << std::endl;
            }
            else if (command == "PATTERN_SUM")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] sum: '" << dts[idx].sum() 
                    << "'" << std::endl;
            }
            else if (command == "SUM_PATTERNS")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "dts[" << idx1 << "] + dts[" << idx2 << "] = '" 
                    << dts[idx1]+dts[idx2] << "'" << std::endl;
            }
            else if (command == "DIFF_PATTERNS")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "dts[" << idx1 << "] - dts[" << idx2 << "] = '" 
                    << dts[idx1]-dts[idx2] << "'" << std::endl;
            }
            else if (command == "MULT_PATTERNS")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "dts[" << idx1 << "] * dts[" << idx2 << "] = '" 
                    << dts[idx1]*dts[idx2] << "'" << std::endl;
            }
            else if (command == "DIV_PATTERNS")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "dts[" << idx1 << "] / dts[" << idx2 << "] = '" 
                    << dts[idx1]/dts[idx2] << "'" << std::endl;
            }
            else if (command == "MULT_C")
            {
                int idx1;
                float c;
                input_line >> idx1 >> c;
                std::cout << c << "* dts[" << idx1 << "] = '" 
                    << c*dts[idx1] << "'" << std::endl;
            }
            else if (command == "MULT_C_INPLACE")
            {
                int idx1;
                float c;
                input_line >> idx1 >> c;
                dts[idx1]*=c;
                std::cout << "dts[" << idx1 << "] *= " << c << " = '" 
                    << dts[idx1] << "'" << std::endl;
            }
            else if (command == "DIV_C")
            {
                int idx1;
                float c;
                input_line >> idx1 >> c;
                std::cout << "dts[" << idx1 << "]/" << c <<" = '" 
                    << dts[idx1]/c << "'" << std::endl;
            }
            else if (command == "DOT_PATTERNS")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "dot(dts[" << idx1 << "], dts[" << idx2 << "]) = '" 
                    << dot(dts[idx1],dts[idx2]) << "'" << std::endl;
            }
            else if (command == "ABS_PATTERN")
            {
                int idx1;
                input_line >> idx1;
                std::cout << "abs(dts[" << idx1 << "]) = '"
                          << dts[idx1].copy().abs() << "'" << std::endl;
            }
            else if (command == "DIST_L1")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "L1(dts[" << idx1 << "], dts[" << idx2 << "]) = '" 
                    << distance_L1(dts[idx1], dts[idx2]) << std::endl;
            }
            else if (command == "DIST_L2")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "L2(dts[" << idx1 << "], dts[" << idx2 << "]) = '" 
                    << distance_L2(dts[idx1], dts[idx2]) << std::endl;
            }
            else if (command == "LOAD_DATASET")
            {
                //input_file.ignore(); //skip newline.
                dts.resize(0);
                std::cout << "Loading dataset: ";
                try {
                    load_dataset(input_file, dts);
                    std::cout << " size = " << dts.size() 
                        << " patterns with dims = " << dts[0].dim() << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "wrong input format" << std::endl;
                    return EXIT_SUCCESS;
                }
            } else if (command == "PRINT_PATTERN")
            {
                int idx;
                input_line >> idx;
                std::cout << "Pattern idx: " << idx << "= " << dts[idx] << std::endl;
            }
            else
            {
                std::cerr << "Error: input command unknown '" << command
                          << "'." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch(std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
