#include "optimization.h"
#include <set>
#include <unordered_map>
#include <vector>
#include <utility>

std::vector<std::set<int>> graph;
std::vector<int> used;
std::vector<int> covered;
std::vector<int> matched_to;
int phase;

std::vector<int> visited_a;
std::vector<int> visited_b;


bool have_new_matching(int v) {
    used[v] = phase;
    for (auto u : graph[v]) {
        if (matched_to[u] == -1 || (used[matched_to[u]] < phase && have_new_matching(matched_to[u]))) {
            if (matched_to[u] > -1) covered[matched_to[u]] -= 1;
            matched_to[u] = v;
            covered[v] = 1;
            return true;
        }
    }
    return false;
}

void do_walk(int v) {
    visited_a[v] = 1;
    for (auto u : graph[v]) {
        if (!visited_a[matched_to[u]]) {
            visited_b[u] = 1;
            do_walk(matched_to[u]);
        }
    }
}

int main() {
    int n_tests = readInt();
    while (n_tests--) {
        int n = readInt(), m = readInt();
        graph.resize(n, {});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                graph[i].insert(j);
            }
            int inverted_edge = readInt();
            while (inverted_edge > 0) {
                graph[i].erase(inverted_edge - 1);
                inverted_edge = readInt();
            }
        }

        used.resize(n, 0);
        covered.resize(n, 0);
        matched_to.resize(m, -1);
        phase = 0;

        bool run = true;
        while (run) {
            run = false;
            phase++;

            for (int i = 0; i < n; ++i) {
                if (covered[i] == 0 && have_new_matching(i)) run = true;
            }
        }

        phase++;
        visited_a.resize(n, 0);
        visited_b.resize(m, 0);

        for (int i = 0; i < n; ++i) {
            if (covered[i] == 0 && !visited_a[i]) {
                do_walk(i);
            }
        }

        int visited_a_count = 0, visited_b_count = 0;
        for (auto item : visited_a) visited_a_count += item;
        for (auto item : visited_b) visited_b_count += (1 - item);

        int total_count = visited_a_count * visited_b_count == 0 ? 0 : visited_a_count + visited_b_count;

        if (total_count == 0) {
            visited_a_count = visited_b_count = 0;
        }

        writeInt(total_count, '\n');
        writeInt(visited_a_count, ' ');
        writeInt(visited_b_count, '\n');
        if (total_count == 0) return 0;
        for (int i = 0; i < n; ++i) {
            if (visited_a[i] > 0) writeInt(i + 1, ' ');
        }
        writeChar('\n');
        for (int j = 0; j < m; ++j) {
            if (visited_b[j] == 0) writeInt(j + 1, ' ');
        }
        writeChar('\n');
        writeChar('\n');

        // CLEARING
        graph.clear();
        used.clear();
        covered.clear();
        matched_to.clear();

        visited_a.clear();
        visited_b.clear();

    }
    return 0;
}