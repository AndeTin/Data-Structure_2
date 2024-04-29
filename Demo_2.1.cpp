#include<iostream>
#include<random>
#include<vector>
#include<ctime>

class Node {
    public:
        class data {
            public:
                int vertex;
                data *next;
                int color;
                int d;
                int f;
                data *pi;
                data() {
                    vertex = 0;
                    next = 0;
                    color = 0;
                    d = 0;
                    f = 0;
                    pi = 0;
                }
        };
        int time = 0;
        int node_count;
        int edge_count;
        int data_count [200] = {0};
        int add_index = 0;
        data *adj_list [200];
        std::vector<data*> stack;
        Node() {
            std::cout << "Please enter the numbers of nodes and edges:\n";
            std::cin >> node_count >> edge_count;
            for (int i = 1; i <= node_count; i++) {
                adj_list[i] = new data;
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
            std::cout << "---------------------Adjacent List---------------------\n";
            for (int i = 1; i <= node_count; i++) {
                std::cout << "Node " << i << "\t| | -> ";
                print_ADL_data(adj_list[i]);
            }
                std::cout << "---------------------Adjacent List---------------------\n";
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
            std::cout << "---------------------Adjacent Matrix---------------------\n";
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
            std::cout << "---------------------Adjacent Matrix---------------------\n";
        }
        void DFS_visit(data *u) {
            if(u->vertex == 0) {
                std::cout << "The graph is empty.\n";
                return;
            }
            u->color = 1;
            u->d = ++time;
            u->pi = 0;
            stack.push_back(u);
            while (u->next != 0) {
                if (u->next->color == 0) {
                    u->next->color = 1;
                    u->next->d = ++time;
                    u->next->pi = u;
                    DFS_visit(u->next);
                }
            }
            u->color = 2;
            u->f = ++time;
            for (int i = 0; i < time/2 + 1; i++) {
                std::cout << stack.back()->vertex << " ";
                stack.pop_back();
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
    std::cout << "DFS_visit: ";
    graph.DFS_visit(graph.adj_list[1]);
    std::cout << "\n";
    return 0;
}