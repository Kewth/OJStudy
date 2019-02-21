#include <bits/stdc++.h>


typedef std::complex<double> complex;

const int maxn = 600050;
complex na[maxn], nb[maxn], E[maxn];
int ra[maxn];

void FFT(complex *a, int n, int type) {
	for(int i=0; i<n; i++)
		if(i < ra[i])
			std::swap(a[i], a[ra[i]]);
	for(int m=2; m<=n; m<<=1) {
		complex Wn(std::cos(M_PI * 2 / m),
				std::sin(M_PI * 2 / m) * type);
		for(int i=0; i<n; i+=m) {
			complex W = 1;
			for(int k=i; k<i+(m>>1); k++) {
				complex a0 = a[k], a1 = a[k + (m >> 1)] * W;
				a[k] = a0 + a1;
				a[k + (m >> 1)] = a0 - a1;
				W *= Wn;
			}
		}
	}
}

int main() {
	int n;
	std::cin >> n;
	n --;
	for(int i=n; i<=(n<<1); i++) {
		double x;
		std::cin >> x;
		na[i] = x;
	}
	for(int i=0; i<n; i++) {
		nb[i] = - double(1) / (i - n) / (i - n);
		nb[(n << 1) - i] = - nb[i];
	}
	int m = 1, l = 0;
	while(m <= n * 3 + 1) {
		m <<= 1;
		l ++;
	}
	for(int i=1; i<m; i++)
		ra[i] = (ra[i >> 1] >> 1) | (i & 1) << (l - 1);
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << na[i].real() << ' '; */
	/* std::clog << std::endl; */
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << nb[i].real() << ' '; */
	/* std::clog << std::endl; */
	FFT(na, m, 1);
	FFT(nb, m, 1);
	for(int i=0; i<m; i++)
		E[i] = na[i] * nb[i];
	FFT(E, m, -1);
	for(int i=0; i<m; i++)
		E[i] /= m;
	std::cout << std::fixed << std::setprecision(3);
	for(int i=n<<1; i<=n*3; i++)
		std::cout << std::setprecision(3)
			<< E[i].real() << std::endl;
	/* for(int i=0; i<m; i++) */
	/* 	std::clog << E[i].real() << ' '; */
	/* std::clog << std::endl; */
}
