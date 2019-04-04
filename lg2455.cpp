#if 0
2019.04.04

高斯消元模板
判断无解或无穷解的情况比较苛刻
一种可行的方法是当主元为 0 的时候尝试与后面的行或列交换，
如果无论怎样交换主元还是 0 ，那么肯定是无穷解或无解，
当前行的系数一定都是 0 ，若常数项非 0 则无解，否则记录下来。
若有记录且之后没有无解的行，则有无穷解。
#endif
#include <bits/stdc++.h>

const int maxn = 105;
double M[maxn][maxn];

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j <= n; j ++)
			std::cin >> M[i][j];
	bool ans0 = false;
	for(int x = 0; x < n; x ++) {
		double Mxx = M[x][x];
		if(std::abs(Mxx) < 1e-6) {
			for(int y = x + 1; y < n; y ++) // 尝试交换行
				if(std::abs(M[y][x]) >= 1e-6) {
					std::swap(M[x], M[y]);
					Mxx = M[x][x];
				}
			if(std::abs(Mxx) < 1e-6) {
				for(int y = x + 1; y < n; y ++) // 尝试交换列
					if(std::abs(M[x][y]) >= 1e-6) {
						for(int i = 0; i < n; i ++)
							std::swap(M[i][x], M[i][y]);
						Mxx = M[x][x];
					}
				if(std::abs(Mxx) < 1e-6) {
					if(std::abs(M[x][n]) >= 1e-6) {
						std::cout << -1 << std::endl;
						return 0;
					} else
						ans0 = true;
				}
			}
		}
		for(int j = 0; j <= n; j ++)
			M[x][j] /= Mxx;
		for(int i = 0; i < n; i ++)
			if(i != x) {
				double Mix = M[i][x];
				for(int j = 0; j <= n; j ++)
					M[i][j] -= Mix * M[x][j];
			}
	}
	if(ans0)
		std::cout << 0 << std::endl;
	else
		for(int i = 0; i < n; i ++)
			if(std::abs(M[i][n]) < 1e-6)
				std::cout << "x" << i + 1 << "=0" << std::endl;
			else
				std::cout << "x" << i + 1 << "=" <<
					std::fixed << std::setprecision(2) <<
					M[i][n] << std::endl;
}
