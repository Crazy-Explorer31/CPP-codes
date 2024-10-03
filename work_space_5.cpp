#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <set>
#include <vector>
#include <string>

using ll = long long;

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

ll push_flow(int v, ll max_flow = INT64_MAX) {
    used[v] = phase;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        Edge& edge = edges[i];
        int to = edges[i].to;
        ll pushed_flow = -1;

        if (used[to] < phase && edge.is_available()) {
            if (to == t || 
                (pushed_flow = push_flow(to, std::min((ll)(edge.capacity - edge.flow), max_flow))) > 0) {
                if (to == t) pushed_flow = std::min((ll)(edge.capacity - edge.flow), max_flow);
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

void mark_S(int v = 0) {
    used[v] = phase;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        Edge& edge = edges[i];
        int to = edge.to;

        if (used[to] < phase && edge.is_available()) {
            mark_S(to);
        }
    }
}

void increasing_flow() {
    ll delta_flow = 0;
    phase++;
    while ((delta_flow = push_flow(s)) > 0) {
        total_flow += delta_flow;
        delta_flow = 0;
        phase++;
    }

    phase++; mark_S();
}

void print_results() {
    // writeInt(total_flow);
    writeChar(' ');
    int count = 0;
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < m; ++i) {
            if ((used[edges[4 * i].from] == phase && used[edges[4 * i].to] < phase) ||
                (used[edges[4 * i].from] < phase && used[edges[4 * i].to] == phase)) {
                    
                    if (j & 1) {
                        writeInt(i + 1, ' ');
                    } else {
                        count++;
                    } 
            }
        }
        if (!(j & 1)) {writeInt(count, ' ');
        writeInt(total_flow, '\n');}
    }
    writeChar('\n');
}

int n, m, s, t;
std::vector<Edge> edges;
std::vector<int> heads;
std::vector<int> used;
int phase = 0;
ll total_flow = 0;
};



int main() {
	Max_Flow_Finder solution;
    solution.increasing_flow();
    solution.print_results();
    return 0;
}