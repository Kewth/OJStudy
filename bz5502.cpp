#if 0
2019.06.02

一位一位考虑，每位转换为 01 矩阵求解。
and 和 or 的求解其实可以相互转化，在此只讨论 or 。
枚举右下角，若当前为 0 ，那么找到其左上所有 1 。
贡献就是这些 1 的左上矩形构成的矩形面积。
这个图形是个锯齿状的，每个齿都是 1 ，那么维护这些齿即可。
#endif
#include <cstdio>

typedef long long lolong;
const int maxn = 1005, mod = 1000000007;
int a[maxn][maxn];
bool b[maxn][maxn];
int sawtooth_x[maxn], sawtooth_y[maxn];
int up[maxn];

lolong tot(int n) {
	lolong res = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			res += i * j;
	return res % mod;
}

lolong calc(int n) {
	int sp = 1, wild = 0;
	lolong res = 0;
	for(int i = 1; i <= n; i ++)
		up[i] = 0;
	for(int i = 1; i <= n; i ++) {
		sawtooth_x[1] = n + 1;
		sawtooth_y[1] = 0;
		sp = 1;
		wild = 0;
		for(int j = 1; j <= n; j ++) {
			if(b[i][j])
				up[j] = i;
			while(sawtooth_x[sp] < up[j]) {
				wild += (up[j] - sawtooth_x[sp])
					* (sawtooth_y[sp] - sawtooth_y[sp - 1]);
				sp --;
			}
			sp ++;
			sawtooth_x[sp] = up[j];
			sawtooth_y[sp] = j;
			wild += up[j];
			res += wild;
		}
	}
	return res % mod;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%d", &a[i][j]);
	lolong ans_and = 0, ans_or = 0;
	for(int k = 0; k < 32; k ++) {
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				b[i][j] = a[i][j] >> k & 1;
		ans_or += 1ll * calc(n) * (1 << k) % mod;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				b[i][j] ^= 1;
		ans_and += 1ll * (tot(n) - calc(n) + mod) * (1 << k) % mod;
	}
	printf("%lld %lld\n", ans_and % mod, ans_or % mod);
}
