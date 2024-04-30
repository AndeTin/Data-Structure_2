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
        int add_index = 0;
        data *adj_list [200];
        std::vector<int> counter;
        std::vector<int> output;

        Node() {
            std::cout << "Please enter the numbers of nodes and edges (nodes < 200):\n";
            std::cin >> node_count >> edge_count;
            if (node_count > 200) {
                std::cout << "The number of nodes is too large.\n";
                return;
            }
            for (int i = 1; i <= node_count; i++) {
                adj_list[i] = new data;
                color[i] = 0;
                pi[i] = 0;
                d[i] = 0;
                f[i] = 0;
            }
        }

        void add_edge(int node1, int node2) {
            if (data_count[node1] == 0) {
                adj_list[node1]->vertex = node2;
                data_count[node1]++;
                if (add_index == 1) {
                add_index = 0;
                return;
                }
                add_index = 1;
                add_edge(node2, node1);
            }
            else {
                data *data_link = adj_list[node1];
                while (data_link->next != 0) {
                    data_link = data_link->next;
                }
                data_link->next = new data;
                data_link->next->vertex = node2;
                data_count[node1]++;
                if (add_index == 1) {
                add_index = 0;
                return;
                }
                add_index = 1;
                add_edge(node2, node1);
            }
            data_count[0]++;
        }

        void print_ADL_data(data *data_link) {
            if (data_link->vertex == 0) {
                std::cout << "|0|0|\n";
                return;
            }
            while(data_link->vertex != 0) {
                std::cout << "|" << data_link->vertex << "|";
                if (data_link->next != 0) {
                    std:: cout << " | -> ";
                    data_link = data_link->next;
                }
                else {
                    std::cout << "0|\n";
                    break;
                }
            }
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
            for (int i = 1; i <= 100; i++) {
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
            d[vertex] = ++time; 
            counter.push_back(vertex);
            data *data_link = adj_list[vertex];
            while (data_link != nullptr) {
                if (color[data_link->vertex] == 0) {
                    pi[data_link->vertex] = vertex; 
                    DFS_visit(data_link->vertex);
                }
                data_link = data_link->next;
            }
            color[vertex] = 2;
            f[vertex] = ++time; 
            output.push_back(vertex);
            counter.pop_back();
        }

        void BFS_visit(int vertex) {
            color[vertex] = 1;
            d[vertex] = ++time;
            counter.push_back(vertex);
            while (!counter.empty()) {
                int current_vertex = counter.front();
                counter.erase(counter.begin());
                data *data_link = adj_list[current_vertex];
                for (int i = 0; i < data_count[current_vertex]; i++) {
                    if (color[data_link->vertex] == 0) {
                        color[data_link->vertex] = 1;
                        d[data_link->vertex] = ++time;
                        counter.push_back(data_link->vertex);
                    }
                    data_link = data_link->next;
                }
                color[current_vertex] = 2;
                f[current_vertex] = ++time;
                std::cout << current_vertex << " ";
            }
        }

        void initialize() {
            for (int i = 1; i <= node_count; i++) {
                color[i] = 0;
                pi[i] = 0;
                d[i] = 0;
                f[i] = 0;
                time = 0;
                counter.clear();
                output.clear();
            }
        
        }
        void print_DFS() {
            std::cout << "DFS_visit: ";
            for (unsigned int i = 0; i < output.size(); i++) {
                std::cout << output[i] << " ";
            }
            std::cout << "\n";
        }

        void output_DFStree() {
            std::ofstream file("DFS_tree.csv");
            if (!file) {
                std::cerr << "Failed to open DFStree file: " << std::endl;
                return;
            }
            for (int i = 1; i <= 200; i++) {
                file << i << "," << pi[i] << "\n";
                file.flush();
            }
            file.close();
        }

        void write_adjacency_list_to_file() {
            std::ofstream file("adjacency_list.csv");
            if (!file) {
                std::cerr << "Failed to open file: adjacency_list.csv" << std::endl;
                return;
            }
            for (int i = 1; i <= 200; i++) {
                data* data_link = adj_list[i];
                while (data_link->vertex != 0) {
                    file << i << "," << data_link->vertex << "\n";
                    file.flush();
                    data_link = data_link->next;
                    if (data_link == 0) {
                        break;
                    }
                }
            }
            file.close();
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
    for(int i = 0; i < graph.edge_count; i++) {
        int node1 = rand() % graph.node_count + 1;
        int node2 = rand() % graph.node_count + 1;
        while (node1 == node2 || graph.check_redundancy(node1, node2)) {
            node1 = rand() % graph.node_count + 1;
            node2 = rand() % graph.node_count + 1;
        }
        graph.add_edge(node1, node2);
    }
    graph.print_ADMatrix();
    graph.print_ADList();
    graph.DFS_visit(1);
    graph.print_DFS();
    graph.initialize();
    std::cout << "BFS_visit: ";
    graph.BFS_visit(1);
    std::cout << "\n";
    graph.write_adjacency_list_to_file();
    return 0;
}