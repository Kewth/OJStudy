#if 0
2019.04.04

矩阵求逆模板
所谓初等变换，把矩阵想象成一个方程组就好了，
只要操作前后方程组等价就 ok 。
#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int maxn = 405, mod = 1000000007;
lolong M[maxn][maxn];
lolong N[maxn][maxn];

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

inline void swap_line(int x, int y, int n) {
	for(int j = 0; j < n; j ++) {
		std::swap(M[x][j], M[y][j]);
		std::swap(N[x][j], N[y][j]);
	}
}

inline void swap_column(int x, int y, int n) {
	for(int i = 0; i < n; i ++) {
		std::swap(M[i][x], M[i][y]);
		std::swap(N[i][x], N[i][y]);
	}
}

inline void line_mul(int x, lolong v, int n) {
	for(int j = 0; j < n; j ++) {
		(M[x][j] *= v) %= mod;
		(N[x][j] *= v) %= mod;
	}
}

inline void line_add_line(int x, int y, lolong v, int n) {
	for(int j = 0; j < n; j ++) {
		(M[x][j] += mod + v * M[y][j]) %= mod;
		(N[x][j] += mod + v * N[y][j]) %= mod;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			std::cin >> M[i][j];
	for(int i = 0; i < n; i ++)
		N[i][i] = 1;
	for(int x = 0; x < n; x ++) {
		if(not M[x][x]) {
			for(int y = x + 1; y < n; y ++) // 尝试交换行
				if(M[y][x])
					swap_line(x, y, n);
			if(not M[x][x]) {
				for(int y = x + 1; y < n; y ++) // 尝试交换列
					if(M[x][y])
						swap_column(x, y, n);
				if(not M[x][x]) {
					std::cout << "No Solution" << std::endl;
					return 0;
				}
			}
		}
		line_mul(x, power(M[x][x], -1), n);
		for(int i = 0; i < n; i ++)
			if(i != x)
				line_add_line(i, x, mod - M[i][x], n);
	}
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++)
			std::cout << N[i][j] << ' ';
		std::cout << std::endl;
	}
}
