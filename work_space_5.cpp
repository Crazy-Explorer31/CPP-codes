#include "optimization.h"
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

struct solution {

solution() {
    m = readInt(), n = readInt();
    graph.resize(m, std::vector<int> (n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) graph[i][j] = j;
        int edge = readInt();
        while (edge > 0) {
            graph[i].erase(std::remove(graph[i].begin(), graph[i].end(), edge - 1), graph[i].end());
            edge = readInt();
        }
    }
    used.resize(m, 0);
    matched_to.resize(n, -1);
    covered.resize(m, 0);
    phase = 0;
}

bool have_increasing_way(int v) {
    used[v] = phase;
    // if (phase % 100 == 0) std::shuffle(graph[v].begin(), graph[v].end(), g);
    for (const auto& u : graph[v]) {
        if (matched_to[u] == -1 || (used[matched_to[u]] < phase && have_increasing_way(matched_to[u]))) {
            if (matched_to[u] > -1 && covered[matched_to[u]] > -1) covered[matched_to[u]] -= 1;
            matched_to[u] = v;
            covered[v] += 1;
            return true;
        }
    }
    return false;
}

void do_walk(int v) {
    used[v] = phase;
    // if (phase % 100 == 0) std::shuffle(graph[v].begin(), graph[v].end(), g);
    for (const auto& u : graph[v]) {
        if (used[matched_to[u]] < phase) {
            visited_right[u] = 1;
            do_walk(matched_to[u]);
        }
    }
    return;
}

void find_matching() {
    bool run = true;
    while (run) {
        run = false;
        phase++;
        for (int i = 0; i < m; ++i) {
            if (used[i] < phase && covered[i] == 0 && have_increasing_way(i)) run = true;
        }
    }
}

void mark_vertexes() {
    phase++;
    visited_right.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        if (covered[i] == 0 && used[i] < phase) do_walk(i);
    }
}

void get_result() {
    int visited_a_count = 0, not_visited_b_count = 0;
    std::vector<int> visited_a, not_visited_b;
    for (int i = 0; i < m; ++i) {
        if (used[i] == phase) {
            visited_a.push_back(i + 1);
            visited_a_count++;
        }
    }
    for (int j = 0; j < n; ++j) {
        if (!visited_right[j]) {
            not_visited_b.push_back(j + 1);
            not_visited_b_count++;
        }
    }
    writeInt(visited_a_count + not_visited_b_count, '\n');
    writeInt(visited_a_count, ' ');
    writeInt(not_visited_b_count, '\n');
    for (auto& item : visited_a) writeInt(item, ' ');
    writeChar('\n');
    for (auto& item : not_visited_b) writeInt(item, ' ');
    writeChar('\n');
    writeChar('\n');
}

int m, n;
std::vector<std::vector<int>> graph;
std::vector<int> used;
std::vector<int> matched_to;
std::vector<int> covered;
int phase;
std::vector<int> visited_right;
};



int main() {
	int n_tests = readInt();
    while (n_tests--) {
        solution s;
        s.find_matching();
        s.mark_vertexes();
        s.get_result();
    }


    return 0;
}