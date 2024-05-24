#include <cstdlib>
#include <iostream>
#include <climits>
#include <cstring>
#include "graph.h"

using namespace std;

class GraphMatrix : public Graph {
    int matrix[10][10];
    char s_vertices[100];
    int num_vert;
    int s_edges[100];
    int num_edge;

public:
    GraphMatrix() : matrix(), s_vertices(), s_edges() {
        memset(matrix, 0, sizeof(matrix));
        num_vert = 0;
        num_edge = 0;
    }

    bool insertVertex(char x)  {
        s_vertices[num_vert] = x;
        num_vert++;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int u_ind = -1, v_ind = -1;
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) {
                u_ind = i;
            }
            if (v == s_vertices[i]) {
                v_ind = i;
            }
        }
        if (u_ind == -1 || v_ind == -1) {
            return false; // Vertex not found
        }
        if (matrix[u_ind][v_ind] != 0) {
            cout << "Edge already exists" << endl;
            return false;
        }
        matrix[u_ind][v_ind] = x;
        matrix[v_ind][u_ind] = x; // Assuming an undirected graph
        s_edges[num_edge] = x;
        num_edge++;
        return true;
    }

    int distance(char u, char v) {
        int u_ind = -1, v_ind = -1;
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) {
                u_ind = i;
            }
            if (v == s_vertices[i]) {
                v_ind = i;
            }
        }
        if (u_ind == -1 || v_ind == -1) {
            return -1; // Vertex not found
        }

        dijkstra(u);
        return matrix[u_ind][v_ind];
    }

    void print() {
        cout << "\t";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
            for (int j = 0; j < num_vert; j++) {
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                } else {
                    cout << "";
                }
                cout << "\t";
            }
            cout << endl;
        }
    }

    void dijkstra(char src) {
        int src_ind = -1;
        for (int i = 0; i < num_vert; i++) {
            if (s_vertices[i] == src) {
                src_ind = i;
                break;
            }
        }
        if (src_ind == -1) {
            cout << "Source vertex not found" << endl;
            return;
        }

        int dist[10];
        bool visited[10];

        for (int i = 0; i < num_vert; i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
        }

        dist[src_ind] = 0;

        for (int count = 0; count < num_vert - 1; count++) {
            int min = INT_MAX, min_index;

            for (int v = 0; v < num_vert; v++) {
                if (!visited[v] && dist[v] <= min) {
                    min = dist[v];
                    min_index = v;
                }
            }

            int u = min_index;
            visited[u] = true;

            for (int v = 0; v < num_vert; v++) {
                if (!visited[v] && matrix[u][v] && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }

        printSolution(dist);
    }

    void printSolution(int dist[]) {
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << " \t\t " << dist[i] << endl;
        }
    }
};