#include <bits/stdc++.h>

typedef std::complex<double> complex;

const int maxn = 600050;
complex a[maxn], b[maxn], c[maxn];
int r[maxn];

void FFT(complex *x, int n, int type) {
	for(int i=0; i<n; i++)
		if(i < r[i])
			std::swap(x[i], x[r[i]]);
	for(int m=2; m<=n; m<<=1) {
		complex Wn(cos(M_PI * 2 / m), sin(M_PI * 2 / m) * type);
		for(int k=0; k<n; k+=m) {
			complex W = 1;
			for(int i=k; i<k+(m>>1); i++) {
				complex a0 = x[i], a1 = x[i + (m >> 1)];
				x[i] = a0 + a1 * W;
				x[i + (m >> 1)] = a0 - a1 * W;
				W *= Wn;
			}
		}
	}
}

int main() {
	int n;
	std::cin >> n;
	n --;
	for(int i=0; i<=n; i++) {
		int x, y;
		std::cin >> x >> y;
		a[i + n] = x;
		b[n - i] = y;
	}
	int m = 1, l = 0;
	while(m <= n * 3) {
		m <<= 1;
		l ++;
	}
	for(int i=1; i<m; i++)
		r[i] = (r[i >> 1] >> 1) | (i & 1) << (l - 1);
	/* std::clog << m << std::endl; */
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << r[i] << ' '; */
	/* std::clog << std::endl; */
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << a[i].real() << ' '; */
	/* std::clog << std::endl; */
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << b[i].real() << ' '; */
	/* std::clog << std::endl; */
	FFT(a, m, 1);
	FFT(b, m, 1);
	for(int i=0; i<m; i++)
		c[i] = a[i] * b[i];
	FFT(c, m, -1);
	for(int i=0; i<m; i++)
		c[i] /= m;
	for(int i=n*2; i<=n*3; i++)
		std::cout << int(c[i].real() + 0.5) << std::endl;
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << int(c[i].real() + 0.5) << ' '; */
	/* std::clog << std::endl; */
}
