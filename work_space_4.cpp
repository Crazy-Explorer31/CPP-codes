// #define FAST_ALLOCATOR_MEMORY
#include "optimization.h"
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

const int n = 1'048'576;
// const int n = 32;
const int bias = n >> 1;

struct node {
	node(int l_ = 0, int r_ = n) : l(l_), r(r_) {
		if (l < r - 1) {
			// int m = l + ((r - l) >> 1);
			// l_son = new node(l, m);
			// r_son = new node(m, r);
		}
	}

	void push() {
		if (l_son && color >= 0) {
			if (color) {
				int m = l + ((r - l) >> 1);
				l_son->black_lb = black_lb;
				l_son->black_rb = m;
				r_son->black_lb = m;
				r_son->black_rb = black_rb;
				l_son->sum = r_son->sum = sum >> 1;
			} else {
				l_son->black_lb = r_son->black_lb = INT32_MAX;
				l_son->black_rb = r_son->black_rb = INT32_MIN;
				l_son->sum = r_son->sum = 0;
			}
			l_son->black_count = r_son->black_count = black_count;
			l_son->color = r_son->color = color;
		}
		color = -1;
	}

	void colorize(int ql, int qr, int new_color) {
		if (l >= qr || r <= ql) return;
		else if (ql <= l && r <= qr) {
			color = new_color;
			black_count = new_color;
			if (color) {
				black_lb = l;
				black_rb = r;
			} else {
				black_lb = INT32_MAX;
				black_rb = INT32_MIN;
			}
			sum = (r - l) * new_color;
			return;
		}

		if (!l_son) {
			int m = l + ((r - l) >> 1);
			l_son = new node(l, m);
			r_son = new node(m, r);
		}
		push();
		l_son->colorize(ql, qr, new_color);
		r_son->colorize(ql, qr, new_color);

		black_lb = std::min(l_son->black_lb, r_son->black_lb);
		black_rb = std::max(l_son->black_rb, r_son->black_rb);
		black_count = l_son->black_count + r_son->black_count - 
			(l_son->black_rb == r_son->black_lb);
		if (black_count == 0) {
			color = 0;
			sum = 0;
		} else if (black_count == 1 && black_lb == l && black_rb == r) {
			color = 1;
			sum = r - l;
		} else {
			sum = l_son->sum + r_son->sum;
		}
	}

	int get_sum() {
		if (color >= 0) {
			return (r - l) * color;
		}
		return l_son->get_sum() + r_son->get_sum();
	}

	int l, r;
	node *l_son = nullptr, *r_son = nullptr;
	int color = 0, black_lb = INT32_MAX, black_rb = INT32_MIN, black_count = 0;
	int sum = 0;
};

int main() {
	int m = readInt();
	int x, l;
	node line(0, n);
	for (int i = 0; i < m; ++i) {
		char color = readChar();
		x = readInt(), l = readInt();
		x += bias;

		if (color == 'W') line.colorize(x, x + l, 0);
		else if (color == 'B') line.colorize(x, x + l, 1);
		
		writeInt(line.black_count, ' ');
		writeInt(line.sum, '\n');
	}


    return 0;
}