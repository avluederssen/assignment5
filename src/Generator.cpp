#include "Generator.h"

Generator::Generator(const Reader& reader): reader(reader), randomEngine(std::random_device{}()){}

std::string Generator::generate(std::size_t length) const
{
    const auto& kgramCounts = reader.getkgramCounts();
    const auto& alphabet = reader.getAlphabet();

    if (kgramCounts.empty()) {
        throw std::runtime_error("The Reader has not been trained.");
    }

    std::vector<std::string> kgrams;
    std::vector<double> frequencies;

    // store the k-grams and their frequencies in two parallel vectors
    for (const auto& entry : kgramCounts) {
        kgrams.push_back(entry.first);
        frequencies.push_back(static_cast<double>(entry.second));
    }

    // choose the starting k-gram according to its frequency
    std::discrete_distribution<std::size_t> kgramDistribution(frequencies.begin(), frequencies.end());
    std::string text = kgrams[kgramDistribution(randomEngine)];

    // generate characters until the requested length is reached
    while (text.size() < length) {
        // The last k characters form the current k-gram
        std::string kgram = text.substr(text.size() - kgrams[0].size());

        std::vector<char> characters;
        std::vector<double> probabilities;

        // get the probability of each possible next character
        for (char c : alphabet) {
            double p = reader.probability(kgram, c);

            characters.push_back(c);
            probabilities.push_back(p);
        }

        // check whether any continuation is possible
        double totalProbability = 0.0;

        for (double p : probabilities) {
            totalProbability += p;
        }

        // with alpha = 0, a k-gram may have no outgoing transitions
        if (totalProbability == 0.0) {
            break;
        }

        // sample the next character according to its probability
        std::discrete_distribution<std::size_t> charDistribution(probabilities.begin(), probabilities.end());
        char nextChar = characters[charDistribution(randomEngine)];

        // append the character to the generated text
        text = text + nextChar;
    }

    return text;
}

