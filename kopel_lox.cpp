#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
/** Interface */

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T> 
inline void writeInt( T x, char end ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;

void print_vector(std::vector<int> a) {
	for (std::size_t i = 0; i < a.size() - 1; ++i) {
		writeInt(a[i], ' ');
	}
	writeInt(a[a.size() - 1], '\n');
}

int main(){
	long long n = readInt(); 
	long long x1 = readInt(), y1 = readInt(), x2 = readInt(), y2 = readInt(); 
	for (int i = 0; i < n - 1; ++i) {
		long long x1_ = readInt(), y1_ = readInt(), x2_ = readInt(), y2_ = readInt(); 
		x1 = std::max(x1, x1_);
		y1 = std::max(y1, y1_);
		x2 = std::min(x2, x2_);
		y2 = std::min(y2, y2_);
	}
	long long ans = (x2 - x1) * (y2 - y1);
	if ((x2 - x1) <= 0 || (y2 - y1) <= 0) {
		writeInt(0, '\n'); 
	} else {
		writeInt(ans, '\n');
	}
	
    return 0;
}