#pragma GCC optimize(2)
#if 0
2019.11.14

学到了新的线性 rmq ，有时间写 blog 。
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

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

struct {
	inline operator int () { int x; return io::gi(x), x; }
} read;

const int maxn = 50005, maxs = 20005, maxb = 80;
int a[maxn + maxb];
int highbit[maxs];
int stmax[maxs][maxb], stmin[maxs][maxb];
int premax[maxs][maxb], premin[maxs][maxb];
int sufmax[maxs][maxb], sufmin[maxs][maxb];
int quemax[maxs][maxb], quemin[maxs][maxb];
int stackmax[maxb], stackmin[maxb];

inline void chkmax(int &x, int y) {
	if(y > x) x = y;
}

inline void chkmin(int &x, int y) {
	if(y < x) x = y;
}

inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int main() {
	int n = read, q = read;
	int B = int(log2(n));
	int S = (n - 1) / B + 1;

	for(int b = 0; b < S; b ++)
		stmin[b][0] = 1000000000;

	for(int i = 0; i < n; i ++) {
		a[i] = read;
		chkmin(stmin[i / B][0], a[i]);
		chkmax(stmax[i / B][0], a[i]);
	}

	for(int b = S - 1; b >= 0; b --)
		for(int k = 1; b + (1 << k) - 1 < S; k ++) {
			stmin[b][k] = min(stmin[b][k - 1], stmin[b + (1 << (k - 1))][k - 1]);
			stmax[b][k] = max(stmax[b][k - 1], stmax[b + (1 << (k - 1))][k - 1]);
		}

	for(int b = 0; b < S; b ++) {
		int be = b * B;
		premin[b][0] = premax[b][0] = a[be];
		for(int k = 1; k < B; k ++) {
			premin[b][k] = min(premin[b][k - 1], a[be + k]);
			premax[b][k] = max(premax[b][k - 1], a[be + k]);
		}
		sufmin[b][B - 1] = sufmax[b][B - 1] = a[be + B - 1];
		for(int k = B - 2; k >= 0; k --) {
			sufmin[b][k] = min(sufmin[b][k + 1], a[be + k]);
			sufmax[b][k] = max(sufmax[b][k + 1], a[be + k]);
		}
	}

	for(int b = 0; b < S; b ++) {
		int be = b * B;
		int spmin = 0, nowmin = 0;
		int spmax = 0, nowmax = 0;
		for(int i = 0; i < B; i ++) {
			while(spmin and a[be + stackmin[spmin]] > a[be + i])
				nowmin ^= 1 << stackmin[spmin --];
			while(spmax and a[be + stackmax[spmax]] < a[be + i])
				nowmax ^= 1 << stackmax[spmax --];
			quemin[b][i] = (nowmin ^= 1 << (stackmin[++ spmin] = i));
			quemax[b][i] = (nowmax ^= 1 << (stackmax[++ spmax] = i));
		}
	}

	for(int i = 2; i <= S; i ++)
		highbit[i] = highbit[i >> 1] + 1;

	while(q --) {
		int l = read - 1;
		int r = read - 1;
		int L = l / B, R = r / B;
		int li = l % B, ri = r % B;

		int min = 1000000000, max = 0;
		if(L == R) {
			chkmin(min, a[l + __builtin_ctz(quemin[R][ri] >> li)]);
			chkmax(max, a[l + __builtin_ctz(quemax[R][ri] >> li)]);
		}
		else {
			chkmin(min, sufmin[L][li]);
			chkmin(min, premin[R][ri]);
			chkmax(max, sufmax[L][li]);
			chkmax(max, premax[R][ri]);
			int len = R - L - 1;
			int k = highbit[len];
			if(len) {
				chkmin(min, stmin[L + 1][k]);
				chkmin(min, stmin[R - (1 << k)][k]);
				chkmax(max, stmax[L + 1][k]);
				chkmax(max, stmax[R - (1 << k)][k]);
			}
		}

		/* printf("%d\n", max - min); */
		io::print(max - min);
		io::pc('\n');
	}
}
