#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <utility>

using ull = unsigned long long;

struct vengry_rulat {

vengry_rulat() {
	n = readInt();
	graph.resize(n, std::vector<ull> (n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			graph[i][j] = readInt();
		}
	}

	visited_a.resize(n, 0), visited_b.resize(n, 0);
	rows_cumulative.resize(n, 0), cols_cumulative.resize(n, 0);
	cols_minimums.resize(n, {-1, -1});
	matched_from_a.resize(n, -1), matched_from_b.resize(n, -1);
	prev.resize(n, -1);
}

void do_purposing() {
	int u;
	int left_end, right_end;
	ull cur_min;
	int cur_min_row, cur_min_col;
	for (int v = 0; v < n; ++v) {
		phase++;
		visited_a[v] = phase;
		for (int j = 0; j < n; ++j) {
			cols_minimums[j] = {graph[v][j] + rows_cumulative[v] + cols_cumulative[j], v};
		}
		u = v;
		while (1) {
			cur_min = UINT64_MAX, cur_min_row = -1, cur_min_col = -1;
			// update cols_minimums
			if (u != v) {
				for (int j = 0; j < n; ++j) {
					if (visited_b[j] < phase && 
						graph[u][j] + rows_cumulative[u] + cols_cumulative[j] < cols_minimums[j].first) {

						cols_minimums[j].first = graph[u][j] + rows_cumulative[u] + cols_cumulative[j];
						cols_minimums[j].second = u;
					}
				}
			}

			for (int j = 0; j < n; ++j) {
				if (visited_b[j] < phase && (cur_min > cols_minimums[j].first)) {
					cur_min = cols_minimums[j].first;
					cur_min_row = cols_minimums[j].second, cur_min_col = j;
				}
			}

			for (int i = 0; i < n; ++i) {
				if (visited_a[i] < phase) {
					rows_cumulative[i] += cur_min;
				}
			}
			for (int j = 0; j < n; ++j) {
				if (visited_b[j] < phase) {
					cols_cumulative[j] -= cur_min;
					cols_minimums[j].first -= cur_min;
				}
			}
			visited_b[cur_min_col] = phase;

			prev[cur_min_col] = cur_min_row;

			u = matched_from_a[cur_min_col]; // new start
			if (u == -1) {
				break; // found increasing way
			}
			visited_a[u] = phase;
			
		}

		left_end = cur_min_row, right_end = cur_min_col;
		int new_right_end;
		while (1) {
			matched_from_a[right_end] = left_end;
			new_right_end = matched_from_b[left_end];
			matched_from_b[left_end] = right_end;

			if (left_end == v) break; // equivalent to
									  // new_right_end == -1

			right_end = new_right_end;
			left_end = prev[right_end];
		}
	}
}

void print_results() {
	ull total_cost = 0;
	for (int j = 0; j < n; ++j) {
		total_cost += graph[matched_from_a[j]][j];
	}
	writeInt(total_cost, '\n');
	for (int i = 0; i < n; ++i) {
		writeInt(i + 1, ' ');
		writeInt(matched_from_b[i] + 1, '\n');
	}
}

int n;
std::vector<std::vector<ull>> graph;
std::vector<int> visited_a, visited_b;
std::vector<int> rows_cumulative, cols_cumulative;
std::vector<std::pair<int, int>> cols_minimums;
std::vector<int> matched_from_a, matched_from_b;
std::vector<int> prev;
int phase = 0;
};

int main() {
	vengry_rulat solution;
	solution.do_purposing();
	solution.print_results();

    return 0;
}