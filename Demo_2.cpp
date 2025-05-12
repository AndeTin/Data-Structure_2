#include<iostream>
#include<random>
#include<vector>
#include<ctime>
#include<fstream>

class Node {
    public:
        class data {
            public:
                int vertex;
                data *next;
                data() {
                    vertex = 0;
                    next = 0;
                }
        };
        int pi[200] ;
        int d[200] ;
        int f[200] ;
        int color[200] ;
        int time = 0;
        int node_count;
        int edge_count;
        int data_count [200] = {0};
        data *adj_list [200];
        std::vector<int> counter;
        std::vector<int> traversal_order; // To store the order of traversal

        Node() {
            std::cout << "Please enter the numbers of nodes and edges (nodes < 200):\n";
            std::cin >> node_count >> edge_count;
            if (node_count > 200) {
                std::cout << "The number of nodes is too large.\n";
                return;
            }
            for (int i = 1; i <= node_count; i++) {
                adj_list[i] = nullptr; // Initialize as nullptr
                color[i] = 0;
                pi[i] = 0;
                d[i] = 0;
                f[i] = 0;
            }
        }

        void add_edge(int node1, int node2) {
            // Check if the edge already exists
            if (check_redundancy(node1, node2)) {
                return; // Do not add the edge if it already exists
            }

            // Add the edge to the adjacency list
            data* new_node = new data;
            new_node->vertex = node2;
            new_node->next = adj_list[node1];
            adj_list[node1] = new_node;

            // Add reverse edge for undirected graph
            new_node = new data;
            new_node->vertex = node1;
            new_node->next = adj_list[node2];
            adj_list[node2] = new_node;

            // Increment the edge count for both nodes
            data_count[node1]++;
            data_count[node2]++;
        }

        void print_ADL_data(data* data_link) {
            if (data_link == nullptr) {
                std::cout << "|0|0|\n";
                return;
            }
            while (data_link != nullptr) {
                std::cout << "|" << data_link->vertex << "|";
                if (data_link->next != nullptr) {
                    std::cout << " | -> ";
                }
                data_link = data_link->next;
            }
            std::cout << "0|\n";
        }

        void print_ADList() {
            std::cout << "---------------------Adjacency List---------------------\n";
            for (int i = 1; i <= node_count; i++) {
                std::cout << "Node " << i << "\t| | -> ";
                print_ADL_data(adj_list[i]);
            }
                std::cout << "---------------------Adjacency List---------------------\n";
        }

        bool check_redundancy(int node1, int node2) {
            if (data_count[node1] == 0) {
                return false;
            }
            else {
                data *data_link = adj_list[node1];
                for (int i = 0; i < data_count[node1]; i++) {
                    if (data_link->vertex == node2) {
                        return true;
                    }
                    else if (data_link->next != 0) {
                        data_link = data_link->next;
                    }
                }
            }
            return false;
        }

        void print_ADMatrix() {
            std::cout << "---------------------Adjacency Matrix---------------------\n";
            std::cout << "\t";
            for (int i = 1; i <= node_count; i++) {
                if (i % 5 == 0) {
                    std::cout << i;
                    if (i < 10) {
                        std::cout << " ";
                    }
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << "\n";

            for (int i = 1; i <= node_count; i++) {
                if (i % 5 == 0) {
                    std::cout << i;
                }
                std::cout << "\t";
                for (int j = 1; j <= node_count; j++) {
                    if (check_redundancy(i, j)) {
                        std::cout << "1 ";
                    }
                    else {
                        std::cout << "0 ";
                    }
                }
                std::cout << "\n";
            }
            std::cout << "---------------------Adjacency Matrix---------------------\n";
        }

        void DFS_visit(int vertex) {
            color[vertex] = 1;
            traversal_order.push_back(vertex); // Record the traversal order
            d[vertex] = ++time;
            data* data_link = adj_list[vertex];
            while (data_link != nullptr) {
                if (color[data_link->vertex] == 0) {
                    pi[data_link->vertex] = vertex;
                    DFS_visit(data_link->vertex);
                }
                data_link = data_link->next;
            }
            color[vertex] = 2;
            f[vertex] = ++time;
        }

        void DFS() {
            for (int i = 1; i <= node_count; i++) {
            if (color[i] == 0) {
                DFS_visit(i);
            }
            }
        }

        void BFS_visit(int vertex) {
            color[vertex] = 1;
            counter.push_back(vertex);
            traversal_order.push_back(vertex); // Record the traversal order
            while (!counter.empty()) {
                int current_vertex = counter.front();
                counter.erase(counter.begin());
                data* data_link = adj_list[current_vertex];
                while (data_link != nullptr) {
                    if (color[data_link->vertex] == 0) {
                        color[data_link->vertex] = 1;
                        d[data_link->vertex] = ++time;
                        pi[data_link->vertex] = current_vertex;
                        counter.push_back(data_link->vertex);
                        traversal_order.push_back(data_link->vertex); // Record the traversal order
                    }
                    data_link = data_link->next;
                }
                color[current_vertex] = 2;
            }
        }

        void BFS() {
            for (int i = 1; i <= node_count; i++) {
            if (color[i] == 0) {
                BFS_visit(i);
            }
            }
        }

        void initialize() {
            for (int i = 1; i <= node_count; i++) {
                color[i] = 0;
                pi[i] = 0;
                d[i] = 0;
                f[i] = 0;
            }
            time = 0;
            counter.clear();
            traversal_order.clear(); // Clear the traversal order
        }

        // void print_DFS() {
        //     std::cout << "DFS Tree Edges:\n";
        //     for (int i = 1; i <= node_count; i++) {
        //         if (pi[i] != 0) {
        //             std::cout << pi[i] << " -> " << i << "\n";
        //         } else if (color[i] == 0) { // Handle isolated nodes
        //             std::cout << i << " is isolated.\n";
        //         }
        //     }
        // }

        // void print_BFS() {
        //     std::cout << "BFS Tree Edges:\n";
        //     for (int i = 1; i <= node_count; i++) {
        //         if (pi[i] != 0) {
        //             std::cout << pi[i] << " -> " << i << "\n";
        //         } else if (color[i] == 0) { // Handle isolated nodes
        //             std::cout << i << " is isolated.\n";
        //         }
        //     }
        // }

        void output_Tree(const std::string &filename) {
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return;
            }

            // Write parent-child relationships to the main file
            for (int i = 1; i <= node_count; i++) {
                if (pi[i] != 0) { // Include nodes with a valid parent
                    file << i << "," << pi[i] << "\n";
                }
            }

            // Append isolated nodes to the same file
            for (int i = 1; i <= node_count; i++) {
                if (pi[i] == 0 && adj_list[i] == nullptr) { // Check for isolated nodes
                    file << i << "," << i << "\n"; // Destination is the node itself
                }
            }

            file.close();
        }

        //void write_adjacency_list_to_file() {
            //std::ofstream file("adjacency_list.csv");
            //if (!file) {
                //std::cerr << "Failed to open file: adjacency_list.csv" << std::endl;
                //return;
            //}
            //for (int i = 1; i <= node_count; i++) {
                //data* data_link = adj_list[i];
                //while (data_link->vertex != 0) {
                    //file << i << "," << data_link->vertex << "\n";
                    //file.flush();
                    //data_link = data_link->next;
                    //if (data_link == 0) {
                        //break;
                    //}
                //}
            //}
            //file.close();
        //}

        void print_traversal_order(const std::string& method) {
            std::cout << method << " Traversal Order: ";
            for (int node : traversal_order) {
                std::cout << node << " ";
            }
            std::cout << "\n\n";
        }

        void write_edges_to_file(const std::string &filename) {
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return;
            }

            // Write all edges to the file
            for (int i = 1; i <= node_count; i++) {
                data* data_link = adj_list[i];
                while (data_link != nullptr) {
                    if (i < data_link->vertex) { // Avoid duplicate edges in an undirected graph
                        file << i << "," << data_link->vertex << "\n";
                    }
                    data_link = data_link->next;
                }
            }

            // Append isolated nodes to the file
            for (int i = 1; i <= node_count; i++) {
                if (adj_list[i] == nullptr) { // Check for isolated nodes
                    file << i << "," << i << "\n"; // Destination is the node itself
                }
            }

            file.close();
            std::cout << "Edges and isolated nodes have been written to " << filename << "\n";
        }

        ~Node() {
            for (int i = 1; i <= node_count; i++) {
                data *data_link = adj_list[i];
                while (data_link != nullptr) {
                    data *temp = data_link;
                    data_link = data_link->next;
                    delete temp;
                }
            }
        }
};


int main() {
    Node graph;
    if (graph.edge_count > graph.node_count * (graph.node_count - 1) / 2) {
        std::cout << "The number of edges is too large.\n";
        return 0;
    }
    srand(time(0));
    for (int i = 0; i < graph.edge_count; i++) {
        int node1, node2;
        do {
            node1 = rand() % graph.node_count + 1;
            node2 = rand() % graph.node_count + 1;
        } while (node1 == node2 || graph.check_redundancy(node1, node2)); // Regenerate if duplicate or self-loop
        graph.add_edge(node1, node2);
    }
    graph.print_ADMatrix();
    graph.print_ADList();

    // Write all edges to a CSV file
    graph.write_edges_to_file("edges.csv");

    // Initialize before DFS
    graph.initialize();
    graph.DFS();
    graph.print_traversal_order("DFS");
    graph.output_Tree("DFS_tree.csv");

    // Initialize before BFS
    graph.initialize();
    graph.BFS();
    graph.print_traversal_order("BFS");
    graph.output_Tree("BFS_tree.csv");

    system("pause");
    return 0;
}