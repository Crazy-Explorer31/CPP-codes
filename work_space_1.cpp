
#include "optimization.h"

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

typedef unsigned long long ull;

int n;
std::vector<ull> segment_tree;

void build() {
	segment_tree.resize(2*n, 0);
}

void change(int i, ull value) {
	segment_tree[i += n] = value;
	while (i > 1) {
		i >>= 1;
		segment_tree[i] = segment_tree[2*i] + segment_tree[2*i + 1];
	}
}

ull get_sum(int l, int r) {
	ull res = 0;
	for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		if (l & 1) res = res + segment_tree[l++];
		if (!(r & 1)) res = res + segment_tree[r--];
	}
	return res;
}


int main() {
	n = readInt();
	int k = readInt();
	build();
	for (int i = 0; i < k; ++i) {
		char c = readChar();
		if (c == 'A') {
			int i = readInt() - 1;
			ull value = readInt();
			change(i, value);
		} else if (c == 'Q') {
			int l = readInt() - 1, r = readInt() - 1;
			ull res = get_sum(l, r);
			writeInt(res, '\n');
		}
	}


    return 0;
}