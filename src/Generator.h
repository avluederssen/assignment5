#ifndef GENERATOR_H
#define GENERATOR_H

#include "Reader.h"

#include <cstddef>
#include <random>
#include <string>

#include <stdexcept>
#include <vector>

class Generator {
public:
    Generator(const Reader& reader);

    std::string generate(std::size_t length) const;

private:
    const Reader& reader;

    mutable std::mt19937 randomEngine;
};

#endif
