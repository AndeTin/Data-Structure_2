//implementing NodeXL graph using adjacency list
#include<iostream>
#include<random>
#include<vector>
#include<ctime>

class Node {
    public:
        int node_count;
        int edge_count;
        int data_count [200];
        int *adj_list [200];
        int *data_link;
        Node(int node_count, int edge_count) {
            this->node_count = node_count;
            this->edge_count = edge_count;
            std::cout << "Please enter the numbers of nodes and edges:";
            std::cin >> node_count >> edge_count;
            int *adj_list[node_count + 1];
            for (int i = 0; i < node_count; i++) {
                adj_list[i] = new int[2];
                adj_list[i][0] = adj_list[i][1] = 0;
            }
        }
        void add_edge(int node1, int node2) {
            if (data_count[node1] == 0) {
                adj_list[node1][0] = node2;
                data_count[node1]++;
                data_count[0]++;
                add_edge(node2, node1);
            }
            else {
                data_link = adj_list[node1];
                while (data_link[1] != 0) {
                    data_link = data_link[1];
                }
                data_link[1]->data_list = {node2, 0};
                data_count[node1]++;
                data_count[0]++;
                add_edge(node2, node1);
            }
        }
        void print_ADJ_data(*data_link){
            for (int k = 0; k < data_count[node1 + 1]; k++) {
                std::cout << "| " << data_link[0] << " | ";
                if (data_link[1] != 0) {
                    std::cout << data_link[1] << " | -> ";
                    print_ADJ_data(data_link[1]);
                }
                else {
                    std::cout << "0 |";
                }
            }
        }
        void print_ADJ_list() {
            std::cout << "------------------------------------------------\n";
            for (int i = 0; i < node_count; i++) {
                std::cout << "Node " << i + 1 << "\t|   | -> ";
                print_ADJ_data(adj_list[i + 1]);
                std::cout << "------------------------------------------------\n";
            }
        }

        void check_redundancy(int node1, int node2) {
            if (data_count[node1] == 0) {
                break;
            }
            else {
                int *data_link = adj_list[node1];
                while (data_link[1] != 0) {
                    if (data_link[0] == node2) {
                        return true;
                    }
                    else {
                        data_link = data_link[1];
                }
                if (data_link[0] == node2) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
};

int pick_random_nodes(int node_count) {
    int node1, node2;
    node1 = rand() % node_count + 1;
    node2 = rand() % node_count + 1;
    while (node1 == node2 || Node.check_redundancy(node1, node2) {
        node1 = rand() % node_count + 1;
        node2 = rand() % node_count + 1;
    }
    return node1, node2;
}

int main() {
    srand(time(0));
    Node graph(node_count, edge_count);
    for (int i = 0; i < graph.edge_count; i++) {
        add_edge(pick_random_nodes(node_count));
    }
    graph.print_ADJ_list();
    return 0;
}
