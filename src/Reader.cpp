#include "Reader.h"

Reader::Reader(std::size_t k): k(k),  totalkgrams(0)
{
    if (k == 0) {
        throw std::invalid_argument("k must be positive.");
    }
}

void Reader::train(const std::string& text)
{
    if (text.size() <= k) {
        throw std::invalid_argument(
            "Training text must contain a k-gram followed by a character."
        );
    }

    alphabet.clear();
    kgramcounts.clear();
    transitions.clear();
    totalkgrams = 0;

    // collect all distinct characters, creating the alphabet
    for (char c : text) {
        alphabet.insert(c);
    }

    
    for (std::size_t i = 0; i + k <= text.size(); ++i) {
        std::string kgram = text.substr(i, k);
        //count all k-grams
        ++kgramcounts[kgram]; 
        ++totalkgrams;
        //count the characters following each k-gram if there is one
        if (i + k < text.size()) {
            char nextChar = text[i + k];
            ++transitions[kgram][nextChar];
        }
    }
}

double Reader::getkgramFrequency(const std::string& kgram) const
{
    if (kgram.size() != k) {
        throw std::invalid_argument("k-gram has the wrong length.");
    }

    auto iterator = kgramcounts.find(kgram);

    if (iterator == kgramcounts.end()) {
        return 0.0;
    }
    
    // count is the number how often a specific k-gram occurs
    std::size_t count = iterator->second;

    //frequency is the number of a specific k-gram divided by the total number of k-grams
    return static_cast<double>(count) / totalkgrams;
}

double Reader::probability(const std::string& kgram, char c) const
{
    if (kgram.size() != k) {
        throw std::invalid_argument("k-gram has the wrong length.");
    }

    if (alphabet.find(c) == alphabet.end()) {
        return 0.0;
    }

    std::size_t charcount = 0;
    std::size_t totalTransitions = 0;

    auto iterator = transitions.find(kgram);

    if (iterator != transitions.end()) {
         //count all transitions following this k-gram
        for (const auto& entry : iterator->second) {
            totalTransitions += entry.second;
        }
        //chariterator is the number how often a specific char follows this k-gram
        auto chariterator = iterator->second.find(c);

        if (chariterator != iterator->second.end()) {
            charcount = chariterator->second;
        }
    }
    if (totalTransitions == 0) {
        return 0.0;
    }
    //probability is the number of a specific char after k-gram divided by all the transitions
    return static_cast<double>(charcount) / totalTransitions;
}

const std::set<char>& Reader::getAlphabet() const
{
    return alphabet;
}

