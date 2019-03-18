#if 0
2019.03.18

Burnside 裸题？
去你大爷的，计算稳定化子还不是得 DP ，
设 f[b][i][j][k] 表示考虑当前置换的第 b 个循环，
三种颜色分别为 i, j, k 的方案数。
置换中的一个循环中的颜色必须一致，根据这个转移。

卧槽我竟然写完后只改一个地方就 A 了，难得难得。
#endif
#include <bits/stdc++.h>

const int maxn = 21, maxm = 61;
int f[maxn * 3][maxn][maxn][maxn];
std::vector<int> gr[maxm];
int to[maxn * 3];
bool vis[maxn * 3];

int dfs(int u) {
	vis[u] = true;
	int v = to[u];
	if(vis[v])
		return 1;
	return dfs(v) + 1;
}

int inv(int x, int mod) {
	int k = mod - 2, res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int s1, s2, s3, m, mod;
	std::cin >> s1 >> s2 >> s3 >> m >> mod;
	int n = s1 + s2 + s3;
	for(int i = 1; i <= n; i ++)
		gr[0].push_back(1);
	for(int j = 1; j <= m; j ++) {
		for(int i = 1; i <= n; i ++)
			std::cin >> to[i];
		for(int i = 1; i <= n; i ++)
			vis[i] = false;
		for(int i = 1; i <= n; i ++)
			if(not vis[i])
				gr[j].push_back(dfs(i));
	}
	int ans = 0;
	for(int g = 0; g <= m; g ++) {
		int gsz = int(gr[g].size());
		f[0][0][0][0] = 1;
		std::clog << "_______" << std::endl;
		for(int b = 1; b <= gsz; b ++) {
			int cur = gr[g][unsigned(b - 1)];
			std::clog << cur << std::endl;
			f[b][0][0][0] = 1;
			for(int i = 0; i <= s1; i ++)
				for(int j = 0; j <= s2; j ++)
					for(int k = 0; k <= s3; k ++) {
						int &now = f[b][i][j][k];
						now = not i and not j and not k;
						if(i >= cur) now += f[b - 1][i - cur][j][k];
						if(j >= cur) now += f[b - 1][i][j - cur][k];
						if(k >= cur) now += f[b - 1][i][j][k - cur];
						now %= mod;
					}
		}
		(ans += f[gsz][s1][s2][s3]) %= mod;
	}
	(ans *= inv(m + 1, mod)) %= mod;
	std::cout << ans << std::endl;
}
