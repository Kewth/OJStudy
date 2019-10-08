#if 0
date +%Y.%m.%d

IO 优化，感谢 @CYJian 提供模板。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr, flg;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () {
		fwrite (obuf, 1, size_t(oS - obuf), stdout);
		oS = obuf;
	}
	inline void pc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I>
	inline int gi (I &x) {
		for (f = 1, c = gc(); c != EOF && (c < '0' || c > '9'); c = gc()) if (c == '-') f = -1;
		for (flg = x = 0; c != EOF && c <= '9' && c >= '0'; c = gc()) flg = 1, x = x * 10 + (c & 15); x *= f;
		return flg || c != EOF;
	}
	template <class I>
	inline void print (I x) {
		if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) pc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: print;
using io :: pc;

int main() {
	int x, y = 0;
	while(gi(x)) {
		print(x);
		pc('\n');
		y ^= x;
	}
	print(y);
	pc('\n');
}
