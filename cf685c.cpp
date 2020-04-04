#if 0
2020.01.31

三维曼哈顿转切比雪夫？
对于点 (x, y, z) 唯一对应四元组 (a, b, c, d) 满足：
a = x + y + z
b = x + y - z
c = x - y + z
d = - x + y + z
那么两点的曼哈顿距离就是两个四元组的切比雪夫距离。

二分曼哈顿距离 x ，判断是否存在整点 p 使得所有点到其的曼哈顿距离不超过 x ，
先判断是否存在四元组 P 使得所有四元组到其切比雪夫距离不超过 x ，
这个是很好判断的，每个四元组对 P 的限制就是每个维度一个不等式。
求得 P 需要满足的条件（四个不等式）后，
考虑从 P 反推 p ，
由于 a = b + c + d ，把 a 代换掉，贪心解可行的 b, c, d 即可，
其中 b, c, d 的奇偶性必须相同，否则得到的 p 不是整点。

总是奇奇怪怪地 WA 在 #6 ，原因不明，换个写法就 A 了。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005;
const ll lim = 3000000000000000000;
ll pos[4][maxn];

ll L[4], R[4];
ll get[4];
bool check(ll r, int n) {
	// debug("check %lld\n", r);
	for(int k = 0; k < 4; k ++) {
		L[k] = - lim * 2;
		R[k] = lim * 2;
		for(int i = 1; i <= n; i ++) {
			L[k] = std::max(L[k], pos[k][i] - r);
			R[k] = std::min(R[k], pos[k][i] + r);
		}
	}

	for(int o = 0; o < 2; o ++) {
		ll Lo[4], Ro[4];
		for(int k = 0; k < 4; k ++) {
			Lo[k] = (L[k] & 1) == o ? L[k] : L[k] + 1;
			Ro[k] = (R[k] & 1) == o ? R[k] : R[k] - 1;
			if(Lo[k] > Ro[k]) goto FAIL;
			get[k] = Lo[k];
		}
#define sum (get[1] + get[2] + get[3])
		if(sum > Ro[0]) goto FAIL;
		for(int k = 1; k <= 3; k ++)
			if(sum < Lo[0]) {
				if(sum - get[k] + Ro[k] <= Lo[0])
					get[k] = Ro[k];
				else
					get[k] = Lo[0] + get[k] - sum;
			}
		if(sum < Lo[0]) goto FAIL;
#undef sum
		// debug("get %lld %lld %lld\n", get[1], get[2], get[3]);
		return 1;
FAIL:;
	}

	return 0;
}

int main() {
	int T = read;
	while(T --) {
		int n = read;
		for(int i = 1; i <= n; i ++) {
			ll x = read, y = read, z = read;
			pos[0][i] = x + y + z;
			pos[1][i] = x + y - z;
			pos[2][i] = x - y + z;
			// pos[3][i] = x - y - z;
			pos[3][i] = - x + y + z;
		}

		ll l = 0, r = lim;
		while(l < r) {
			ll mid = (l + r) >> 1;
			if(check(mid, n))
				r = mid;
			else
				l = mid + 1;
		}

		check(l, n);

		ll x, y, z;
		printf("%lld %lld %lld\n",
				x = (get[1] + get[2]) >> 1,
				y = (get[1] + get[3]) >> 1,
				z = (get[2] + get[3]) >> 1);

#if 0
		debug("%lld\n", l);
		for(int k = 0; k < 4; k ++)
			debug("%lld ~ %lld\n", L[k], R[k]);
		debug("%lld %lld %lld %lld\n",
				x + y + z,
				x + y - z,
				x - y + z,
				- x + y + z);
		debug("%lld %lld %lld %lld\n",
				x + y + z, get[1], get[2], get[3]);
#endif
	}
}
