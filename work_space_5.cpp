#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>

const int n = 1'048'576;
// const int n = 16;
const int bias = n >> 1;

struct node {
	node(int l_ = 0, int r_ = n) : l(l_), r(r_), value_key(l_) {}

	void push() {
		value += pending;
        if (l + 1 >= r) {
            pending = 0;
            return;
        }
        if (!l_son) {
            int m = l + ((r - l) >> 1);
            l_son = new node(l, m);
            r_son = new node(m, r);
        }
        l_son->pending += pending;
        r_son->pending += pending;
        pending = 0;
	}

	void add(int ql, int qr, int one) {
		if (l >= qr || r <= ql) return;
		else if (ql <= l && r <= qr) {
			pending += one;
            return;
		}

		push();
		l_son->add(ql, qr, one);
		r_son->add(ql, qr, one);

		if (l_son->value + l_son->pending > r_son->value + r_son->pending) {
            value = l_son->value + l_son->pending;
            value_key = l_son->value_key;
        } else {
            value = r_son->value + r_son->pending;
            value_key = r_son->value_key;
        }
	}

	int l, r, value_key, value = 0, pending = 0;
	node *l_son = nullptr, *r_son = nullptr;
};

int main() {
    node tree(0, n);
	int m = readInt();
    std::vector<std::tuple<int, int, int, int>> bounds(2 * m);
    int x1, y1, x2, y2;
    for (int i = 0; i < 2 * m;) {
        x1 = readInt(), y1 = readInt(), x2 = readInt(), y2 = readInt();
        bounds[i++] = {x1, y1, y2, 0};
        bounds[i++] = {x2, y1, y2, 1};
    }
    std::sort(bounds.begin(), bounds.end(), [](const std::tuple<int, int, int, int>& lhs, const std::tuple<int, int, int, int>& rhs) {
        if (std::get<0>(lhs) == std::get<0>(rhs)) {
            return std::get<3>(lhs) < std::get<3>(rhs);
        }
        return std::get<0>(lhs) < std::get<0>(rhs);
    });

    int res = -1;
    int x_res, y_res;
    for (const auto& bound : bounds) {
        int x = std::get<0>(bound);
        int y1 = std::get<1>(bound), y2 = std::get<2>(bound);
        int t = std::get<3>(bound);
        if (t == 0) {
            tree.add(y1 + bias, y2 + bias + 1, 1);
            if (tree.value + tree.pending > res) {
                res = tree.value + tree.pending;
                x_res = x, y_res = tree.value_key - bias;
            }
        } else if (t == 1) {
            tree.add(y1 + bias, y2 + bias + 1, -1);
        }
    }

    writeInt(res, '\n');
    writeInt(x_res, ' ');
    writeInt(y_res, '\n');


    return 0;
}