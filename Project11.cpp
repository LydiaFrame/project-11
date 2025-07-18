/*
    Name: Lydia Frame
    Date: July 18, 2025
    Project 11 - Topological Sort
    Description:
    This program builds a directed graph from a user-input connectivity matrix.
    It then performs a topological sort on the graph and displays the sorted order.
*/

#include <iostream>
#include <vector>
#include <queue>

class GraphNode {
private:
    int topNum; // For topological sort

public:
    int pointNum;
    std::vector<GraphNode*> connectedNodes;

    GraphNode(int num) : pointNum(num), topNum(-1) {}

    void setTopNum(int num) {
        topNum = num;
    }

    int getTopNum() const {
        return topNum;
    }
};

class Graph {
private:
    std::vector<GraphNode*> nodes;

public:
    // Constructor
    Graph(const std::vector<std::vector<int>>& matrix) {
        int size = matrix.size();

        for (int i = 0; i < size; ++i) {
            nodes.push_back(new GraphNode(i));
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] == 1) {
                    nodes[i]->connectedNodes.push_back(nodes[j]);
                }
            }
        }
    }

    // Destructor
    ~Graph() {
        for (GraphNode* node : nodes) {
            delete node;
        }
        nodes.clear();
    }

    // Display graph structure
    void displayGraph() const {
        for (const GraphNode* node : nodes) {
            std::cout << "Node " << node->pointNum << " connects to: ";
            for (const GraphNode* neighbor : node->connectedNodes) {
                std::cout << neighbor->pointNum << " ";
            }
            std::cout << std::endl;
        }
    }

    // Topological sort (based on Figure 9.7 pseudocode)
    void topsort() {
        std::vector<int> indegree(nodes.size(), 0);

        // Step 1: Compute indegrees
        for (GraphNode* node : nodes) {
            for (GraphNode* neighbor : node->connectedNodes) {
                indegree[neighbor->pointNum]++;
            }
        }

        std::queue<GraphNode*> q;

        // Step 2: Enqueue nodes with zero indegree
        for (GraphNode* node : nodes) {
            if (indegree[node->pointNum] == 0) {
                q.push(node);
            }
        }

        int counter = 0;

        // Step 3: Process the queue
        while (!q.empty()) {
            GraphNode* v = q.front();
            q.pop();

            v->setTopNum(counter++);

            for (GraphNode* neighbor : v->connectedNodes) {
                indegree[neighbor->pointNum]--;
                if (indegree[neighbor->pointNum] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Display sorted result
        std::vector<GraphNode*> sorted(nodes.size());

        for (GraphNode* node : nodes) {
            sorted[node->getTopNum()] = node;
        }

        std::cout << "\nTopological Sort Order:\n";
        for (GraphNode* node : sorted) {
            std::cout << "Node " << node->pointNum << " (TopNum = " << node->getTopNum() << ")\n";
        }
    }
};

int main() {
    int N;
    std::cout << "Enter number of nodes: ";
    std::cin >> N;

    std::vector<std::vector<int>> matrix(N, std::vector<int>(N));

    std::cout << "Enter the connectivity matrix (each row of " << N << " values, 1 for edge, 0 for no edge):\n";

    for (int i = 0; i < N; ++i) {
        std::cout << "Row " << i << ": ";
        for (int j = 0; j < N; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    Graph g(matrix);

    std::cout << "\nGraph structure:\n";
    g.displayGraph();

    g.topsort();

    return 0;
}
