#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

typedef long long ll;

int n_old, n;
std::vector<ll> segment_tree;
std::vector<ll> pendings;

ll max(ll a, ll b) {
    return std::max(a, b);
}

ll min(ll a, ll b) {
    return std::min(a, b);
}



void ceil_n() {
    int k = 1;
    while (k < n_old) k <<= 1;
    n = k;
}

void build() {
    segment_tree.resize(2*n, INT64_MIN);
    for (int i = 0; i < n_old; ++i) {
        segment_tree[i + n] = readInt();
    }
    for (int i = n - 1; i > 0; --i) {
        segment_tree[i] = max(segment_tree[i << 1], segment_tree[(i << 1) | 1]);
    }

    pendings.resize(2*n, 0);
}

void push(int i) {
    segment_tree[i] += pendings[i];

    if (((i << 1) | 1) < (n << 1)){
        pendings[i << 1] += pendings[i];
        pendings[(i << 1) | 1] += pendings[i];
    }
    pendings[i] = 0;
}

void add(int i, int il, int ir, int l, int r, int value) {
    if (max(il, l) >= min(ir, r)) return;
    if (l <= il && ir <= r) {
        pendings[i] += value;
        return;
    }
    push(i);

    int m = il + ((ir - il) >> 1);
    add((i << 1), il, m, l, r, value);
    add(((i << 1) | 1), m, ir, l, r, value);
    segment_tree[i] = max(
        segment_tree[i << 1] + pendings[i << 1], 
        segment_tree[(i << 1) | 1] + pendings[(i << 1) | 1]
    ) + pendings[i];
}

ll get_max(int i, int il, int ir, int l, int r) {
    if (max(il, l) >= min(ir, r)) return INT64_MIN;
    push(i);
    if (l <= il && ir <= r) return segment_tree[i];

    int m = il + ((ir - il) >> 1);
    ll left_max = get_max((i << 1), il, m, l, r);
    ll right_max = get_max(((i << 1) | 1), m, ir, l, r);
    return max(left_max, right_max);
}


int main() {
	n_old = readInt();
    ceil_n();
    int q = readInt();
    build();
    int l, r;
    ll value;
    for (int i = 0; i < q; ++i) {
        char c = readChar();
        readChar(); readChar();
        l = readInt() - 1;
        r = readInt() - 1;
        if (c == 'a') {
            value = readInt();
            add(1, 0, n, l, r + 1, value);
        } else if (c == 'm') {
            ll res = get_max(1, 0, n, l, r + 1);
            writeInt(res, '\n');
        }
    }


    return 0;
}