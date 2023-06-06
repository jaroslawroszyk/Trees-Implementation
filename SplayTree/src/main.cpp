#include "../include/SplayTree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>

struct Measurement
{
    int dataSize;
    double comparisons;
    double accesses;
    double maxHeight;
};

// Funkcja do generowania losowych permutacji
std::vector<int> generateRandomPermutation(int n)
{
    std::vector<int> permutation(n);
    for (int i = 0; i < n; i++)
    {
        permutation[i] = i + 1;
    }
    std::random_shuffle(permutation.begin(), permutation.end());
    return permutation;
}

int main()
{
    // Inicjalizacja drzewa Splay
    SplayTree splayTree;

    // Rozmiary danych
    std::vector<int> dataSizes = {10000, 20000, 30000, 40000, 50000};

    // Przeprowadzenie eksperymentów dla różnych rozmiarów danych
    std::vector<Measurement> measurements;
    for (int dataSize : dataSizes)
    {
        Measurement measurement;
        measurement.dataSize = dataSize;

        // Wstawianie rosnącego ciągu
        // Wstawianie rosnącego ciągu
        splayTree = SplayTree();
        for (int i = 1; i <= dataSize; i++)
        {
            splayTree.insert(i);
        }
        measurement.comparisons = splayTree.getComparisons();
        measurement.accesses = splayTree.getAccesses();
        measurement.maxHeight = *std::max_element(splayTree.getHeights().begin(), splayTree.getHeights().end());

        measurements.push_back(measurement);

        // Usuwanie losowego ciągu
        splayTree = SplayTree(); // Resetowanie drzewa Splay
        std::vector<int> randomSequence = generateRandomPermutation(dataSize);
        for (int key : randomSequence)
        {
            splayTree.insert(key);
        }
        for (int key : randomSequence)
        {
            splayTree.deleteNode(key);
        }
        measurement.comparisons = splayTree.getComparisons();
        measurement.accesses = splayTree.getAccesses();
        measurement.maxHeight = *std::max_element(splayTree.getHeights().begin(), splayTree.getHeights().end());

        measurements.push_back(measurement);
    }

    // Zapis wyników do pliku
    std::ofstream outputFile("results.txt");
    if (outputFile.is_open())
    {
        for (const auto &measurement : measurements)
        {
            outputFile << measurement.dataSize << ","
                       << measurement.comparisons << ","
                       << measurement.accesses << ","
                       << measurement.maxHeight << "\n";
        }
        outputFile.close();
        std::cout << "Results saved to results.txt" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open results.txt" << std::endl;
    }

    return 0;
}
