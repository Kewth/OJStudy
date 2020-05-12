#if 0
2020.05.11

  构造卷积，设 f[i] = sum((s[i + j] - t[j]) s[i] t[j]) ，其中字母被映射到一个唯一的正值
而问号被映射到 0 。那么 f[i] = 0 就代表这个位置匹配。
#endif
#include <cstdio>
#include <cstring>
#include <complex>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxl = 1 << 18;
typedef std::complex<double> complex;
int R[maxl];
complex Wn[maxl];

void init (int n) {
    for (int i = 1; i < n; i ++)
		R[i] = R[i >> 1] >> 1 | ((i & 1) * (n >> 1));
    for (int i = 0; i < n; i ++)
		Wn[i] = complex(cos(M_PI / n * i), sin(M_PI / n * i));
}

void DFT (complex *A, int n) {
	for (int i = 0; i < n; i ++)
		if (i < R[i])
			std::swap(A[i], A[R[i]]);
	for (int m = 1; m < n; m <<= 1)
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				complex a0 = A[k], a1 = A[k + m] * Wn[n / m * (k - i)];
				A[k] = a0 + a1;
				A[k + m] = a0 - a1;
			}
}

void IDFT (complex *A, int n) {
	std::reverse(A + 1, A + n);
	DFT(A, n);
	for(int i = 0; i < n; i ++)
		A[i] /= n;
}

ll num (complex x) {
	double y = x.real();
	return y < 0 ? ll(y - 0.5) : ll(y + 0.5);
}

const int maxn = 100005;
char s[maxn], t[maxn];
ll f[maxn];
complex a[maxl], b[maxl], aa[maxl], bb[maxl];

int main () {
	scanf("%s%s", s, t);

	int n = int(strlen(s)), m = int(strlen(t));
	std::reverse(t, t + m);

	ll x = 0;
	for (int i = 0; i < n; i ++) {
		a[i] = s[i] - 'a' + 1;
		aa[i] = a[i] * a[i];
	}
	for (int i = 0; i < m; i ++) {
		b[i] = t[i] == '?' ? 0 : t[i] - 'a' + 1;
		bb[i] = b[i] * b[i];
		x += int((b[i] * b[i] * b[i]).real());
	}

	int len = 1;
	while (len < n + m) len <<= 1;
	init(len);

	DFT(a, len);
	DFT(aa, len);
	DFT(b, len);
	DFT(bb, len);
	for (int i = 0; i < len; i ++) {
		aa[i] *= b[i];
		bb[i] *= a[i];
	}
	IDFT(aa, len);
	IDFT(bb, len);

	for (int i = m - 1; i < n + m - 1; i ++)
		f[i - m + 1] = num(aa[i] - bb[i] - bb[i]) + x;

	int ans = 0;
	for (int i = 0; i + m - 1 < n; i ++)
		if (f[i] == 0)
			++ ans;

	printf("%d\n", ans);
	for (int i = 0; i + m - 1 < n; i ++)
		if (f[i] == 0)
			printf("%d\n", i);
}
