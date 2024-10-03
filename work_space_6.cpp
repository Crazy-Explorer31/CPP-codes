#include "optimization.h"
#include <cstdint>
#include <set>
#include <vector>
#include <string>

using ll = long long;
using ull = unsigned long long;

struct Edge {
Edge() {}
Edge(int from, int to, int flow, int capacity, int next_edge) : 
    from(from), to(to), flow(flow), capacity(capacity), next_edge(next_edge) {}

bool is_available(ll weight) { return flow + weight <= capacity; }
bool is_positive() { return flow > 0; }

int from, to;
ll flow, capacity;
int next_edge;
};

struct Max_Flow_Finder {
Max_Flow_Finder() {
    n = readInt(), m = readInt();
    s = 0, t = n - 1;
    edges.reserve(2 * m);
    heads.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int from = readInt(), to = readInt(), capacity = readInt();
        from--, to--;

        edges.push_back(Edge(from, to, 0, capacity, heads[from]));
        edges.push_back(Edge(to, from, 0, 0, heads[to]));
        heads[from] = 2 * i;
        heads[to] = 2 * i + 1;
    }
    used.resize(n, 0);
}

bool push_flow(int v, ll trial_flow) {
    used[v] = phase;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        Edge& edge = edges[i];
        int to = edges[i].to;

        if (used[to] < phase && edge.is_available(trial_flow)) {
            if (to == t || push_flow(to, trial_flow)) {
                edge.flow += trial_flow;
                edges[i ^ 1].flow -= trial_flow;
                // res_paths.back().push_back((i >> 1) + 1); // too early
                return 1;
            }
        }
    }
    return 0;
}

int pop_flow(int v, int cur_min = INT32_MAX) {
    used[v] = phase;
    int new_min;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        int next_min = std::min(cur_min, (int)(edges[i].flow));
        if (next_min <= 0) continue;
        if (edges[i].flow > 0 && used[edges[i].to] < phase && 
            (edges[i].to == t || (new_min = pop_flow(edges[i].to, next_min)) > 0)) {
            
            if (edges[i].to == t) {
                new_min = next_min;
            }

            edges[i].flow -= new_min;
            
            res_paths.back().push_back((i >> 1) + 1);
            return new_min;
        }
    }
    return 0;
}

void increasing_flow() {
    ll trial_flow = (1 << 30);
    for (; trial_flow > 0; trial_flow = (trial_flow >> 1)) {
        while ((phase++, push_flow(s, trial_flow))) {}
    }

    int got_flow = 0;
    (phase++, res_paths.push_back({}));
    while ((got_flow = pop_flow(s))) {
        res_flows.push_back(got_flow);
        (phase++, res_paths.push_back({}));
    }
    res_paths.pop_back();
}

void print_results() {
    writeInt(res_paths.size(), '\n');
    for (int i = 0; i < res_paths.size(); ++i) {
        writeInt(res_flows[i], ' ');
        writeInt(res_paths[i].size(), ' ');
        for (int j = res_paths[i].size() - 1; j >= 0; --j) {
            writeInt(res_paths[i][j], ' ');
        }
        writeChar('\n');
    }
}

int n, m, s, t;
std::vector<Edge> edges;
std::vector<int> heads;
std::vector<int> used;
int phase = 0;
std::vector<int> res_flows;
std::vector<std::vector<int>> res_paths;
};



int main() {
	Max_Flow_Finder solution;
    solution.increasing_flow();
    solution.print_results();
    return 0;
}