// NEED TO DEBUG ON
// 5 7
// 1 2
// 2 3
// 3 1
// 3 4
// 4 5
// 1 2
// 5 3



#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <random>

std::random_device rd;
std::mt19937 g(rd());

struct finding_max_matching {
finding_max_matching() {
    n = readInt(), m = readInt();
    graph.resize(n, {});
    for (int e = 0; e < m; ++e) {
        int a = readInt(), b = readInt();
        graph[a - 1].push_back(b - 1), graph[b - 1].push_back(a - 1);
    }
    used.resize(n, 0);
    pair.resize(n, -1);
    covered.resize(n, 0);
    phase = 0;
}

bool have_incresing_way(int v) {
    std::shuffle(graph[v].begin(), graph[v].end(), g);
    used[v] = phase;
    for (auto u : graph[v]) {
        if (pair[u] == -1 || (used[pair[u]] < phase && have_incresing_way(pair[u]))) {
            if (pair[u] == -1) covered[u] = 1;

            pair[u] = v;
            pair[v] = u;
            return true;
        }
    }
    return false;
}

void search_max_matching() {
    bool run = true;
    while (run) {
        run = false;
        phase++;
        for (auto& item : used) item = 0;
        for (int i = 0; i < n; ++i) {
            if (!covered[i] && have_incresing_way(i)) {
                covered[i] = 1;
                run = true;
            }
        }
    }
}

void print_results() {
    int total_covered = 0;
    for (int i = 0; i < n; ++i) {
        total_covered += covered[i];
    }
    writeInt(total_covered / 2, '\n');

    for (int i = 0; i < n; ++i) {
        if (covered[i]) {
            writeInt(i + 1, ' ');
            writeInt(pair[i] + 1, '\n');
            covered[i] = covered[pair[i]] = 0;
        }
    }
}


int n, m;
std::vector<std::vector<int>> graph;
std::vector<int> used;
std::vector<int> pair;
std::vector<int> covered;
int phase;
};


int main() {
	finding_max_matching solution;
    solution.search_max_matching();
    solution.print_results();


    return 0;
}