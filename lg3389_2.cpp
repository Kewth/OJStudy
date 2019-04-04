#if 0
2019.04.04

高斯消元模板
#endif
#include <bits/stdc++.h>

const int maxn = 105;
double M[maxn][maxn];

int fuck() {
	std::cout << "No Solution" << std::endl;
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j <= n; j ++)
			std::cin >> M[i][j];
	for(int x = 0; x < n; x ++) {
		double Mxx = M[x][x];
		if(std::abs(Mxx) < 1e-6)
			return fuck();
		for(int j = 0; j <= n; j ++)
			M[x][j] /= Mxx;
		for(int i = 0; i < n; i ++)
			if(i != x) {
				double Mix = M[i][x];
				for(int j = 0; j <= n; j ++)
					M[i][j] -= Mix * M[x][j];
			}
	}
	for(int i = 0; i < n; i ++)
		std::cout << std::fixed << std::setprecision(2)
			<< M[i][n] << std::endl;
}
