#if 0
2019.10.26

emm 被卡常了，看来还是不能动不动就重构块。
然而根据常数分布微调块大小还是可以的。

分块，区间加不难处理，
询问的话维护每个块每个权值的数量，
对于询问点 p 首先暴力扫 p 所在的块，然后再扫完整的块，
对于完整的块，由于维护了权值分布，可以 O(1) 查询有没有与 p 相同的值，
如果有，暴力扫描这个块，然后往这个方向的块就不用管了。
区间左移的话可以考虑在每个块内维护环状结构，然后记一个开头的位置，
完整的块区间左移会进来一个数出去一个数，特判这两种，
然后剩下的部分直接把开头位置向右移即可，由于维护的是环，这相当于整体进行了左移。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxb = 640, maxs = 640, maxn = 100005;
int s[maxs][maxb];
int tot[maxs][maxn << 1];
int offset[maxs], tag[maxs];
int B, S;

void modify(int b, int p, int x) {
	int &v = s[b][p];
	tot[b][v] --;
	v = x;
	tot[b][v] ++;
}

void shift_all(int b, int in, int &out) {
	in -= tag[b];
	out = s[b][offset[b]];
	modify(b, offset[b], in);
	offset[b] ++;
	if(offset[b] == B) offset[b] = 0;
	out += tag[b];
}

void search_all(int b, int p, int &ans) {
	for(int i = b * B; i / B == b; i ++)
		if(i != p and s[b][i % B] == s[p / B][p % B])
			ans = std::min(ans, std::abs(i - p));
}

int tmp[maxb];
void pulldown(int b) {
	if(tag[b]) {
		for(int i = 0; i < B; i ++)
			modify(b, i, s[b][i] + tag[b]);
		tag[b] = 0;
	}
	if(offset[b]) {
		for(int i = 0; i < B; i ++)
			tmp[i] = s[b][(offset[b] + i) % B];
		for(int i = 0; i < B; i ++)
			s[b][i] = tmp[i];
		offset[b] = 0;
	}
}

int main() {
	int n = input(), q = input();
	B = (int(sqrt(n)) << 1);
	S = n / B + 1;

	for(int i = 0; i < n; i ++) {
		int x = s[i / B][i % B] = input();
		tot[i / B][x] ++;
	}

	while(q --) {
		int op = input();

		if(op == 1) {
			int l = input() - 1, r = input() - 1;

			if(l / B == r / B) {
				pulldown(l / B);
				int in = s[l / B][l % B];
				for(int i = l % B; i < r % B; i ++)
					modify(l / B, i, s[l / B][i + 1]);
				modify(r / B, r % B, in);
			}

			else {
				pulldown(l / B);
				pulldown(r / B);
				int in = s[l / B][l % B], out;

				out = s[r / B][0];
				for(int i = 0; i < r % B; i ++)
					modify(r / B, i, s[r / B][i + 1]);
				modify(r / B, r % B, in);

				for(int b = r / B - 1; b > l / B; b --)
					shift_all(b, out, out);

				in = out;
				/* out = s[l / B][l % B]; */
				for(int i = l % B; i < B - 1; i ++)
					modify(l / B, i, s[l / B][i + 1]);
				modify(l / B, B - 1, in);
			}
		}

		else if(op == 2) {
			int l = input() - 1, r = input() - 1;

			if(l / B == r / B) {
				pulldown(l / B);
				for(int i = l; i <= r; i ++)
					modify(i / B, i % B, s[i / B][i % B] + 1);
			}

			else {
				pulldown(l / B);
				pulldown(r / B);

				for(int i = l; i / B == l / B; i ++)
					modify(i / B, i % B, s[i / B][i % B] + 1);
				for(int i = r; i / B == r / B; i --)
					modify(i / B, i % B, s[i / B][i % B] + 1);

				for(int b = l / B + 1; b < r / B; b ++)
					tag[b] ++;
			}
		}

		else if(op == 3) {
			int p = input() - 1;
			pulldown(p / B);
			int x = s[p / B][p % B];
			int ans = 1000000000;

			search_all(p / B, p, ans);

			for(int b = p / B - 1; b >= 0 and (p / B - 1 - b) * B < ans; b --)
				if((p / B - 1 - b) * B < ans and x > tag[b] and tot[b][x - tag[b]]) {
					pulldown(b);
					search_all(b, p, ans);
				}

			for(int b = p / B + 1; b < S and (b - p / B - 1) * B < ans; b ++)
				if(x > tag[b] and tot[b][x - tag[b]]) {
					pulldown(b);
					search_all(b, p, ans);
				}

			if(ans == 1000000000) puts("-1");
			else printf("%d\n", ans);
		}

		/* for(int i = 0; i < B * B; i ++) */
		/* 	debug(" %d", s[i / B][i % B]); */
		/* debug("\n"); */
	}
}
