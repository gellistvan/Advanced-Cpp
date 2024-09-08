#include <bitset>
#include <iostream>
#include <vector>

const int NUM_NODES = 5;

int main() {
    // Adjacency matrix for a graph with 5 nodes
    std::vector<std::bitset<NUM_NODES>> adjacency_matrix(NUM_NODES);

    // Add edges
    adjacency_matrix[0][1] = 1;
    adjacency_matrix[1][0] = 1; // Undirected edge between node 0 and 1
    adjacency_matrix[1][2] = 1;
    adjacency_matrix[2][1] = 1;
    adjacency_matrix[2][3] = 1;
    adjacency_matrix[3][2] = 1;
    adjacency_matrix[3][4] = 1;
    adjacency_matrix[4][3] = 1;

    // Print adjacency matrix
    std::cout << "Adjacency Matrix:" << std::endl;
    for (const auto& row : adjacency_matrix) {
        std::cout << row << std::endl;
    }

    return 0;
}