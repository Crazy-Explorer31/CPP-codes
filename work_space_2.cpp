#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

const int n = 32'000 + 1;
std::vector<int> segment_tree(2 * n, 0);

void reset() {
    std::fill(segment_tree.begin(), segment_tree.end(), 0);
}

void change(int i, int value) {
	segment_tree[i += n] += value;
	while (i > 1) {
		i >>= 1;
		segment_tree[i] = segment_tree[i << 1] + segment_tree[(i << 1) | 1];
	}
}

int get_sum(int r, int l = 0) {
	int res = 0;
	for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		if (l & 1) res = res + segment_tree[l++];
		if (!(r & 1)) res = res + segment_tree[r--];
	}
	return res;
}


int main() {
	int m;
    bool first = true;
    int x, y;
    std::vector<int> ans;
    while (m = readInt()) {
        if (!first) reset();
        ans.resize(m, 0);
        std::fill(ans.begin(), ans.end(), 0);
        for (int i = 0; i < m; ++i) {
            x = readInt(), y = readInt();
            int res = get_sum(x);
            ans[res] += 1;
            
            change(x, 1);
        }
        for (auto& item : ans) {
            std::cout << item << '\n';
        }

        first = false;
    }


    return 0;
}