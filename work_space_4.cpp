#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <set>
#include <vector>
#include <string>

struct MinStack {
void push(int a) {
    data.push_back(a);
    mins.push_back((mins.empty() || mins.back() >= a) ? (a) : (mins.back()));
}

void pop() {
    data.pop_back();
    mins.pop_back();
}

int get_min() { return mins.back(); }

void clear() {
    data.clear();
    mins.clear();
}

std::vector<int> data;
std::vector<int> mins;
};

struct Edge {
Edge() {}
Edge(int from, int to, int flow, int capacity, int next_edge) : 
    from(from), to(to), flow(flow), capacity(capacity), next_edge(next_edge) {}

bool is_available() { return flow < capacity; }
bool is_positive() { return flow > 0; }

int from, to, flow, capacity;
int next_edge;
};

struct Max_Flow_Finder {
Max_Flow_Finder() {
    n = readInt(), m = readInt();
    s = 0, t = n - 1;
    edges.reserve(4 * m);
    heads.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int from = readInt(), to = readInt(), capacity = readInt();
        from--, to--;

        edges.push_back(Edge(from, to, 0, capacity, heads[from]));
        edges.push_back(Edge(to, from, 0, 0, heads[to]));
        heads[from] = 4 * i;
        heads[to] = 4 * i + 1;
        
        edges.push_back(Edge(to, from, 0, capacity, heads[to]));
        edges.push_back(Edge(from, to, 0, 0, heads[from]));
        heads[to] = 4 * i + 2;
        heads[from] = 4 * i + 3;
    }
    used.resize(n, 0);
}

int push_flow(int v, int max_flow = INT32_MAX) {
    used[v] = phase;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        Edge& edge = edges[i];
        int to = edges[i].to;
        int pushed_flow = -1;

        if (used[to] < phase && edge.is_available()) {
            if (to == t || 
                (pushed_flow = push_flow(to, std::min(edge.capacity - edge.flow, max_flow))) > 0) {
                if (to == t) pushed_flow = std::min(edge.capacity - edge.flow, max_flow);
                if (pushed_flow > 0) {
                    edge.flow += pushed_flow;
                    edges[i ^ 1].flow -= pushed_flow;
                    return pushed_flow;
                }
            }
        }
    }
    return 0;
}

void increasing_flow() {
    int delta_flow = 0;
    phase++;
    while ((delta_flow = push_flow(s)) > 0) {
        total_flow += delta_flow;
        delta_flow = 0;
        phase++;
        max_flows.clear();
    }
}

void print_results() {
    writeDouble(total_flow, 3);
    writeChar('\n');
    for (int i = 0; i < m; ++i) {
        writeDouble(edges[4 * i].flow - edges[4 * i + 2].flow, 3);
        writeChar('\n');
    }
}

int n, m, s, t;
std::vector<Edge> edges;
std::vector<int> heads;
std::vector<int> used;
MinStack max_flows;
int phase = 0;
int total_flow = 0;
};



int main() {
	Max_Flow_Finder solution;
    solution.increasing_flow();
    solution.print_results();
    return 0;
}