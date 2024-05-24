class Graph {
public:
    virtual int distance(char u, char v) = 0;
    virtual bool insertVertex(char x) = 0;
    virtual bool insertEdge(char u, char v, int x) = 0;
    virtual void print() = 0;
};