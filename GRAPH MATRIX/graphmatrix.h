#include <cstdlib>
#include <iostream>
#include <cstring>
#include "graph.h"
using namespace std;

class GraphMatrix : public Graph {
    int matrix[10][10];
    char s_vertices[10];
    int num_vert;
    int s_edges[100];
    int num_edge;
    int num_edges_inserted;


    int findVertexIndex(char v) {
        for (int i = 0; i < num_vert; ++i) {
            if (s_vertices[i] == v) {
                return i;
            }
        }
        return -1;
    }

public:
    GraphMatrix() {
        num_vert = 0;
        num_edge = 0;
        num_edges_inserted = 0;
        memset(s_edges, 0, sizeof(s_edges));

    }

    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        return s_vertices;
    }

    int numEdges() {
        return num_edge;
    }


    int* edges() {
        return s_edges;
    }

    int getEdge(char u, char v)  {
        int ui = findVertexIndex(u);
        int vi = findVertexIndex(v);
        if (ui == -1 || vi == -1) {
            return 0;
        }
        return matrix[ui][vi];
    }

    char* endVertices(int e) {
        char* verts = new char[2];
        verts[0] = '-';
        verts[1] = '-';
        for (int i = 0; i < num_vert; ++i) {
            for (int j = 0; j < num_vert; ++j) {
                if (matrix[i][j] == e) {
                    verts[0] = s_vertices[i];
                    verts[1] = s_vertices[j];
                    return verts;
                }
            }
        }
        return verts;
    }

    char opposite(char v, int e) {
        int vi = findVertexIndex(v);
        if (vi == -1) {
            return '-';
        }
        for (int i = 0; i < num_vert; ++i) {
            if (matrix[vi][i] == e) {
                return s_vertices[i];
            } else if (matrix[i][vi] == e) {
                return s_vertices[i];
            }
        }
        return '-';
    }


    int outDegree(char v) {
        int vi = findVertexIndex(v);
        if (vi == -1) {
            return 0;
        }
        int degree = 0;
        for (int j = 0; j < num_vert; ++j) {
            if (matrix[vi][j] != 0) {
                degree++;
            }
        }
        return degree;
    }

    int inDegree(char v) {
        int vi = findVertexIndex(v);
        if (vi == -1) {
            return 0;
        }
        int degree = 0;
        for (int i = 0; i < num_vert; ++i) {
            if (matrix[i][vi] != 0) {
                degree++;
            }
        }
        return degree;
    }

    int* outgoingEdges(char v) {
        int vi = findVertexIndex(v);
        if (vi == -1) {
            return NULL;
        }
        int* edges = new int[outDegree(v)];
        int k = 0;
        for (int j = 0; j < num_vert; ++j) {
            if (matrix[vi][j] != 0) {
                edges[k++] = matrix[vi][j];
            }
        }
        return edges;
    }

    int* incomingEdges(char v) {
        int vi = findVertexIndex(v);
        if (vi == -1) {
            return NULL;
        }
        int* edges = new int[inDegree(v)];
        int k = 0;
        for (int i = 0; i < num_vert; ++i) {
            if (matrix[i][vi] != 0) {
                edges[k++] = matrix[i][vi];
            }
        }
        return edges;
    }

    bool insertVertex(char x)  {
        if(num_vert == 10){
            return false;
        }
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int ui = findVertexIndex(u);
        int vi = findVertexIndex(v);
        if (ui == -1 || vi == -1 || matrix[ui][vi] != 0) {
            return false;
        }
        matrix[ui][vi] = x;
        s_edges[num_edges_inserted++] = x;
        num_edge++;
        return true;
    }

    int removeVertex(char v) {
        int vi = findVertexIndex(v);
        if (vi == -1) {
            return 0;
        }
        int removedEdges = 0;
        for (int i = 0; i < num_vert; ++i) {
            if (matrix[vi][i] != 0) {
                matrix[vi][i] = 0;
                removedEdges++;
            }
            if (matrix[i][vi] != 0) {
                matrix[i][vi] = 0;
                removedEdges++;
            }
        }
        for (int i = vi; i < num_vert - 1; ++i) {
            s_vertices[i] = s_vertices[i + 1];
            for (int j = 0; j < num_vert; ++j) {
                matrix[i][j] = matrix[i + 1][j];
                matrix[j][i] = matrix[j][i + 1];
            }
        }
        num_vert--;
        num_edge -= removedEdges;
        return removedEdges;
    }

    bool removeEdge(int e) {
        for (int i = 0; i < num_vert; ++i) {
            for (int j = 0; j < num_vert; ++j) {
                if (matrix[i][j] == e) {
                    matrix[i][j] = 0;
                    num_edge--;
                    return true;
                }
            }
        }
        return false;
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
                }
                cout << "\t";
            }
            cout << endl;
        }
    }
};