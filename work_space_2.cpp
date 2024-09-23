#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <map>
#include <vector>
#include <string>
#include <set>

std::vector<std::vector<int>> graph;
std::vector<int> used;
std::vector<int> matched_to;
std::vector<int> covered;

bool have_new_matching(int v) {
    used[v] = 1;
    for (auto u : graph[v]) {
        if (matched_to[u] == -1 ||
            used[matched_to[u]] == 0 && have_new_matching(matched_to[u])) {
                if (matched_to[u] > -1) covered[matched_to[u]] -= 1;
                matched_to[u] = v;
                covered[v] += 1;
                return true;
            }
    }
    return false;
}

int main() {
	int n = readInt(), m = readInt();
    graph.resize(n, {});
    used.resize(n, 0);
    matched_to.resize(m, -1);
    covered.resize(n, 0);

    for (int i = 0; i < n; ++i) {
        int b_neighbor = readInt();
        while (b_neighbor != 0) {
            graph[i].push_back(b_neighbor - 1);
            b_neighbor = readInt();
        }
    }

    bool run = true;
    while (run) {
        run = false;
        for (auto& item : used) item = 0;

        for (int i = 0; i < n; ++i) {
            if (covered[i] == 0 && have_new_matching(i)) run = true;
        }
    }

    int matchings_count = 0;
    for (auto item : matched_to) {
        if (item != -1) matchings_count++;
    }
    writeInt(matchings_count, '\n');
    for (int i = 0; i < m; ++i) {
        if (matched_to[i] != -1) {
            writeInt(matched_to[i] + 1, ' ');
            writeInt(i + 1, '\n');
        }
    }
    return 0;
}