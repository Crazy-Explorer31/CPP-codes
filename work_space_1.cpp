#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <set>

std::vector<std::vector<int>> graph;
std::vector<int> visited_a;
std::vector<int> visited_b;
std::vector<int> matched_to;
std::vector<int> covered;

void try_to_increase(int v) {
	visited_a[v] = 1;
	for (auto u : graph[v]) {
		if (!visited_a[matched_to[u]]) {
			visited_b[u] = 1;
			try_to_increase(matched_to[u]);
		}
	}
	return;
}

int main() {
	int m = readInt(), n = readInt();
	graph.resize(m, {});
	visited_a.resize(m, 0);
	visited_b.resize(n, 0);
	matched_to.resize(n, -1);
	covered.resize(m, 0);

	for (int i = 0; i < m; ++i) {
		int neighbors_count = readInt();
		graph[i].resize(neighbors_count, 0);
		for (int j = 0; j < neighbors_count; ++j) {
			graph[i][j] = readInt() - 1;
		}
	}

	for (int i = 0; i < m; ++i) {
		int matched_to_i = readInt();
		if (matched_to_i == 0) continue;

		matched_to[matched_to_i - 1] = i;
		covered[i] = 1;
	}

	for (int i = 0; i < m; ++i) {
		if (!covered[i] && !visited_a[i]) 
			try_to_increase(i);
	}

	int visited_a_count = 0, visited_b_count = 0;
	for (int i = 0; i < m; ++i) {
		visited_a_count += (1 - visited_a[i]);
	}
	for (int j = 0; j < n; ++j) {
		visited_b_count += visited_b[j];
	}

	writeInt(visited_a_count + visited_b_count, '\n');

	writeInt(visited_a_count, ' ');
	for (int i = 0; i < m; ++i) {
		if (!visited_a[i]) writeInt(i + 1, ' ');
	}
	writeChar('\n');

	writeInt(visited_b_count, ' ');
	for (int j = 0; j < n; ++j) {
		if (visited_b[j]) writeInt(j + 1, ' ');
	}
	writeChar('\n');


    return 0;
}