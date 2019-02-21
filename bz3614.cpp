#include <bits/stdc++.h>

typedef long long lint;

const int maxn = 20;
lint num[1 << maxn];
char s[maxn];

int rader(int x, int n) {
	int res = 1, l = 0;
	while(res < n) {
		res <<= 1;
		l ++;
	}
	res = 0;
	for(int i=0; i<l; i++)
		if(x >> i & 1)
			res |= 1 << (l - i - 1);
	/* std::clog << x << " -> " << res << std::endl; */
	return res;
}

void FFT(lint *a, int n, int type) {
	/* for(int i=0; i<n; i++) */
	/* 	std::clog << a[i] << ' '; */
	/* std::clog << std::endl; */
	for(int i=0; i<n; i++) {
		int r = rader(i, n);
		if(i < r)
			std::swap(a[i], a[r]);
	}
	for(int m=2; m<=n; m<<=1) {
		for(int i=0; i<n; i+=m) {
			for(int k=i; k<i+(m>>1); k++) {
				lint a0 = a[k], a1 = a[k + (m >> 1)];
				a[k] = a0 + a1;
				a[k + (m >> 1)] = a0 - a1;
			}
		}
	}
	/* for(int i=0; i<n; i++) */
	/* 	std::clog << a[i] << ' '; */
	/* std::clog << std::endl; */
}

lint gcd(lint a, lint b) {
	if(not b)
		return a;
	return gcd(b, a % b);
}

void print_ans(int i, int n) {
	lint a = num[i];
	if(not a)
		return ;
	lint b = 100 * (1 << n);
	lint g = gcd(std::abs(a), b);
	a /= g;
	b /= g;
	if(b > 1)
		std::cout << a << '/' << b;
	else
		std::cout << a;
	if(i) {
		std::cout << ' ';
		for(int k=0; k<n; k++)
			if(i >> k & 1)
				std::cout << 'x' << k + 1;
	}
	std::cout << std::endl;
	num[i] = 0;
}

void ans_print(int id, int n, int now) {
	if(id == n) {
		print_ans(now, n);
		return ;
	}
	ans_print(n, n, now);
	ans_print(id + 1, n, now | (1 << id));
	ans_print(id + 1, n, now);
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i=0; i<(1<<n); i++) {
		std::cin >> s;
		int now = 0;
		for(int j=0; j<n; j++)
			if(s[j] == '-')
				now |= 1 << (n - j - 1);
		double f;
		std::cin >> f;
		if(f > 0)
			num[now] = lint(f * 100 + 0.5);
		else
			num[now] = lint(f * 100 - 0.5);
	}
	FFT(num, 1 << n, -1);
	ans_print(0, n, 0);
}
