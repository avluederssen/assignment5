#include "Reader.h"
#include "Generator.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
    try {
        double alpha = 0.0;
        int argumentIndex = 1;

        // read the optional alpha argument
        if (argc > 1 && std::string(argv[1]) == "-a") {
            if (argc < 6) {
                throw std::invalid_argument(
                    "Usage: ./slm [-a alpha] k filename length"
                );
            }

            alpha = std::stod(argv[2]);

            if (alpha < 0.0 || !std::isfinite(alpha)) {
                throw std::invalid_argument(
                    "Alpha must be non-negative and finite."
                );
            }

            argumentIndex = 3;
        }

        // check the number of arguments
        if (argc - argumentIndex != 3) {
            throw std::invalid_argument(
                "Usage: ./slm [-a alpha] k filename length"
            );
        }

        // read k
        std::string kText = argv[argumentIndex];
        std::size_t k = std::stoull(kText);

        if (k == 0) {
            throw std::invalid_argument("k must be a positive integer.");
        }

    
        // read the filename
        std::string filename = argv[argumentIndex + 1];

        // read lenght of new text
        std::string lengthText = argv[argumentIndex + 2];
       
        std::size_t length = std::stoull(lengthText);

        if (length < k) {
            throw std::invalid_argument(
                "Length must be at least k."
            );
        }

        // open and read the training file
        std::ifstream file(filename);

        if (!file) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        // temporarily store the file content into a buffer as a string
        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string trainingText = buffer.str();

        // train the Reader
        Reader reader(k, alpha);
        reader.train(trainingText);

        // generate and print the text
        Generator generator(reader);
        std::cout << generator.generate(length) << std::endl;

    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}