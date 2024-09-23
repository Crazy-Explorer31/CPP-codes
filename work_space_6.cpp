#include "optimization.h"
#include "stdio.h"
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

struct order {
order() {}
void assign_order(int hh_, int mm_, int a_, int b_, int c_, int d_) {
    hh = hh_, mm = mm_, a = a_, b = b_, c = c_, d = d_;
}

int hh, mm, a, b, c, d;
};

bool can_be_after(const order& fst, const order& snd) {
    int time_had = 60 * (snd.hh - fst.hh) + (snd.mm - fst.mm);
    // if (time_had <= 0) return false;

    int time_to_complete = abs(fst.a - fst.c) + abs(fst.b - fst.d);
    int time_to_arrive = abs(fst.c - snd.a) + abs(fst.d - snd.b);
    int time = time_to_complete + time_to_arrive;

    if (time_had - time <= 0) return false;
    return true;
}

struct solution {
solution() {
    n = readInt();
    std::vector<order> orders(n);
    for (int i = 0; i < n; ++i) {
        int hh = readInt();
        // readChar();
        int mm = readInt(), a = readInt(), b = readInt(), c = readInt(), d = readInt();
        // scanf("%d\:%d %d %d %d %d", &hh, &mm, &a, &b, &c, &d);
        orders[i].assign_order(hh, mm, a, b, c, d);
    }
    graph.resize(n, {});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (can_be_after(orders[i], orders[j])) {
                graph[i].push_back(j);
            }
        }
    }
    used.resize(n, 0);
    covered.resize(n, 0);
    matched_to.resize(n, -1);
    matched_from.resize(n, -1);
    phase = 0;
    res = n;
}

bool have_increasing_way(int v) {
    used[v] = phase;
    for (const auto& u : graph[v]) {
        if (matched_to[u] == -1 || (used[matched_to[u]] < phase && have_increasing_way(matched_to[u]))) {
            if (matched_to[u] > -1 && covered[matched_to[u]] > -1) covered[matched_to[u]] -= 1;
            matched_to[u] = v;
            matched_from[v] = u;
            covered[v] += 1;
            return true;
        }
    }
    return false;
}

void find_matching() {
    bool run = true;
    while (run) {
        run = false;
        phase++;
        for (int i = 0; i < n; ++i) {
            if (used[i] < phase && covered[i] == 0 && have_increasing_way(i)) {
                run = true;
                res--;
            }
        }
    }
}

void mark_way(int v) {
    used[v] = phase;
    if (used[matched_from[v]] < phase && matched_from[v] != -1) {
        mark_way(matched_from[v]);
        res--;
    }
} 

int get_ways_count() {
    phase++;
    for (int i = 0; i < n; ++i) {
        if (used[i] < phase) {
            mark_way(i);
        }
    }
    return res;
}

int n;
std::vector<std::vector<int>> graph;

std::vector<int> used;
std::vector<int> covered;
std::vector<int> matched_to;
std::vector<int> matched_from;
int phase;
int res;
};

int main() {
	solution s;
    s.find_matching();
    // int res = s.get_ways_count();
    int res = s.res;
    writeInt(res, '\n');
    return 0;
}