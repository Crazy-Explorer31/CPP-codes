#include "optimization.h"
#include <set>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>

std::random_device rd;
std::mt19937 g(rd());

int n, m;
std::vector<std::vector<int>> graph;

std::vector<int> used;
std::vector<int> covered;
std::vector<int> matched_to;

int phase = 0;

int get_hash(int a, int b) {
    return a * m + b;
}

bool good(int a, int b) {
    return (0 <= a && a < n && 0 <= b && b < m);
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

int main() {
    n = readInt(), m = readInt();
    int a = readInt(), b = readInt();

    std::vector<std::vector<int>> nodes_map (n, std::vector<int> (m));
    int bad_nodes_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = ' ';
            while (c != '.' && c != '*') c = readChar();

            if (c == '.') {
                nodes_map[i][j] = 0;
            } else {
                nodes_map[i][j] = 1;
                bad_nodes_count++;
            }
        }
    }
    if (a >= b*2) {
        writeInt(b * bad_nodes_count, '\n');
        return 0;
    }

    graph.resize(n * m, {});

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 0 && nodes_map[i][j] == 1) {
                int center = get_hash(i, j);

                if (good(i - 1, j) && nodes_map[i - 1][j] == 1) {
                    graph[center].push_back(get_hash(i - 1, j));
                } 
                if (good(i + 1, j) && nodes_map[i + 1][j] == 1) {
                    graph[center].push_back(get_hash(i + 1, j));
                }
                if (good(i, j - 1) && nodes_map[i][j - 1] == 1) {
                    graph[center].push_back(get_hash(i, j - 1));
                }
                if (good(i, j + 1) && nodes_map[i][j + 1] == 1) {
                    graph[center].push_back(get_hash(i, j + 1));
                }
            }
        }
    }

    used.resize(n * m, 0);
    covered.resize(n * m, 0);
    matched_to.resize(n * m, -1);
    for (int i = 0; i < n * m; ++i) used[i] = covered[i] = 0;
    for (int i = 0; i < n * m; ++i) matched_to[i] = -1;

    int matchings_count = 0;
    bool run = true;
    while (run) {
        run = false;
        phase++;

        for (int i = 0; i < n * m; ++i) {
            if (covered[i] == 0 && used[i] < phase && have_increasing_way(i)) {
                run = true;
                matchings_count++;
            }
        }
    }

    int res_cost = matchings_count * a + (bad_nodes_count - 2 * matchings_count) * b;

    writeInt(res_cost, '\n');
    return 0;
}