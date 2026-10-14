
#ifndef Reader_H
#define Reader_H

#include <cstddef>
#include <set>
#include <string>
#include <unordered_map>

#include <cmath>
#include <stdexcept>

class Reader {
public:
    Reader(std::size_t k);

    void train(const std::string& text);

    double getkgramFrequency(const std::string& kgram) const;

    double probability(const std::string& kgram, char c) const;

    const std::set<char>& getAlphabet() const;

private:
    std::size_t k;
    double alpha; //later!

    std::set<char> alphabet;

    std::unordered_map<std::string, std::size_t> kgramcounts; //counts how often each k-grams occurs

    using CharCounts = std::unordered_map<char, std::size_t>;
    std::unordered_map<std::string, CharCounts> transitions; //counts how often each character follows each k-gram

    std::size_t totalkgrams;
};

#endif