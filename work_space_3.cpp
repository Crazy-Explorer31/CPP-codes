#include "optimization.h"
#include <unordered_map>
#include <vector>
#include <utility>

struct Edge {
Edge() {}
Edge(int from, int to, int flow, int capacity, int next_edge) : 
    from(from), to(to), flow(flow), capacity(capacity), next_edge(next_edge) {}

bool is_available() { return flow < capacity; }
bool is_positive() { return flow > 0; }

int from, to, flow, capacity;
int next_edge;
};

struct Paths_Finder {
Paths_Finder() {
    n = readInt(), m = readInt(), s = readInt() - 1, t = readInt() - 1;
    edges.resize(2 * m);
    heads.resize(n, -1);
    used.resize(n, 0);
    for (int i = 0; i < 2 * m; i += 2) {
        int from = readInt(), to = readInt();
        from--;
        to--;

        if (from == to) continue; // needed?
        
        edges[i] =   Edge(from, to, 0, 1, heads[from]);
        edges[i^1] = Edge(to, from, 0, 0, heads[to]);

        heads[from] = i;
        heads[to] =   i^1;
    }
    res_paths.resize(2, {});
    phase = 0;
}

bool push_flow(int v) {
    used[v] = phase;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        if (edges[i].is_available() && used[edges[i].to] < phase && 
            (edges[i].to == t || push_flow(edges[i].to))) {
            
            edges[i].flow     += 1;
            edges[i ^ 1].flow -= 1;
            return true;
        }
    }
    return false;
}

bool pop_flow(int v) {
    used[v] = phase;
    for (int i = heads[v]; i != -1; i = edges[i].next_edge) {
        if (edges[i].flow > 0 && used[edges[i].to] < phase && 
            (edges[i].to == t || pop_flow(edges[i].to))) {
            
            edges[i].flow     -= 1;
            
            res_paths[phase - 3].push_back(v);
            return true;
        }
    }
    return false;
}

void find_paths() {
    phase++; push_flow(s);
    phase++; push_flow(s);

    phase++; paths_found = paths_found && pop_flow(s);
    phase++; paths_found = paths_found && pop_flow(s);
}

void print_results() {
    if (paths_found) {
        writeWord("YES\n");

        for (int i = res_paths[0].size() - 1; i > -1; --i) {
            writeInt(res_paths[0][i] + 1, ' ');
        }
        writeInt(t + 1, '\n');

        for (int i = res_paths[1].size() - 1; i > -1; --i) {
            writeInt(res_paths[1][i] + 1, ' ');
        }
        writeInt(t + 1, '\n');
    } else {
        writeWord("NO\n");
    }
}

int n, m, s, t;
std::vector<Edge> edges;
std::vector<int> heads;
std::vector<int> used;
int phase;

std::vector<std::vector<int>> res_paths;

bool paths_found = true;
};

int main() {
    Paths_Finder solution;
    solution.find_paths();
    solution.print_results();


    return 0;
}