#if 0
2019.10.08

快速幂复杂度固然是对的，但是常数略大。
注意到模数 1e9+9 ，此时根号 5 是有二次剩余的。
那么直接套用斐波那契通项公式即可。
然而为了卡矩阵乘法，数据量有点大，需要预处理 + O(1) 快速幂。
然而还是不够，读入 TLE 了解一下？实名 diss CYJian 卡常。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

namespace io {
const int __SIZE = (1 << 13) + 1;
char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55];
int __f, qr, _eof;
#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
inline void flush() { fwrite(obuf, 1, oS - obuf, stdout), oS = obuf; }
inline void gc(char &x) { x = Gc(); }
inline void pc(char x) {
    *oS++ = x;
    if (oS == oT)
        flush();
}
inline void pstr(const char *s) {
    int __len = strlen(s);
    for (__f = 0; __f < __len; ++__f)
        pc(s[__f]);
}
inline void gstr(char *s) {
    for (__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)
        __c = Gc();
    for (; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc())
        *s = __c;
    *s = 0;
}
template <class I> inline bool gi(I &x) {
    _eof = 0;
    for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) {
        if (__c == '-')
            __f = -1;
        _eof |= __c == EOF;
    }
    for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc())
        x = x * 10 + (__c & 15), _eof |= __c == EOF;
    x *= __f;
    return !_eof;
}
template <class I> inline void print(I x) {
    if (!x)
        pc('0');
    if (x < 0)
        pc('-'), x = -x;
    while (x)
        qu[++qr] = x % 10 + '0', x /= 10;
    while (qr)
        pc(qu[qr--]);
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
} // namespace io

typedef long long lolong;

const lolong sqrt5 = 383008016;
const int mod = 1000000009;
const int sqmod = 32000;

lolong pa1[sqmod], pa2[sqmod], pb1[sqmod], pb2[sqmod];

lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	lolong a = (1 + sqrt5 + mod) >> 1;
	lolong b = (1 - sqrt5 + mod) >> 1;
	lolong inv = power(sqrt5, -1);

	pa1[0] = pb1[0] = 1;
	for(int i = 1; i < sqmod; i ++) {
		pa1[i] = pa1[i - 1] * a % mod;
		pb1[i] = pb1[i - 1] * b % mod;
	}

	a = pa1[sqmod - 1] * a % mod;
	b = pb1[sqmod - 1] * b % mod;
	pa2[0] = pb2[0] = 1;
	for(int i = 1; i < sqmod; i ++) {
		pa2[i] = pa2[i - 1] * a % mod;
		pb2[i] = pb2[i - 1] * b % mod;
	}

	int T;
	io::gi(T);
	while(T --) {
		lolong n;
		io::gi(n);
		n %= mod - 1;
		lolong A = pa2[n / sqmod] * pa1[n % sqmod] % mod;
		lolong B = pb2[n / sqmod] * pb1[n % sqmod] % mod;
		io::print((A - B + mod) * inv % mod);
		io::pc('\n');
	}
}
