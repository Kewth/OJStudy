#if 0
2019.08.31

妙啊，整体二分例题。
一个坑点在于算获得的陨石数量时可能爆 long long ，需要在中途判断是否到达需求。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 300005;
std::vector<int> pos[maxn];
int need[maxn];
int ans[maxn];
int boom_l[maxn], boom_r[maxn], boom[maxn];
int shit_l[maxn], shit_r[maxn], shit[maxn];
lolong bit[maxn];

inline void add(int p, int x) {
	for(int k = p; k; k -= k & -k)
		bit[k] += x;
}

inline lolong query(int p) {
	lolong res = 0;
	for(int k = p; k < maxn; k += k & -k)
		res += bit[k];
	return res;
}

void solve(int l, int r, int L, int R) {
	if(l > r)
		return;

	if(L == R) {
		for(int i = l; i <= r; i ++)
			ans[shit[i]] = L;
		return;
	}

	int mid = (L + R) >> 1;
	/* int mid = 1; */

	auto with_bit = [&](int typ) {
		for(int i = L; i <= mid; i ++) {
			add(boom_r[i], boom[i] * typ);
			add(boom_l[i] - 1, - boom[i] * typ);
			if(boom_l[i] > boom_r[i])
				add(maxn - 1, boom[i] * typ);
		}
	};

	with_bit(1);

#if 0
	debug("answer: %d ~ %d\n", L, R);
	for(int i = l; i <= r; i ++)
		debug(" %d", shit[i]);
	debug(" are shit\n");
	for(int i = 1; i <= 10; i ++)
		debug(" %lld", query(i));
	debug(" are bit\n");
	for(int i = l; i <= r; i ++) {
		lolong get = 0;
		for(int p : pos[shit[i]])
			get += query(p);
		debug("oh, %d get %lld which need %d!\n", shit[i], get, need[shit[i]]);
	}
#endif

	int pl = 0, pr = 0;
	for(int i = l; i <= r; i ++) {
		lolong get = 0;
		bool got_it = false;
		for(int p : pos[shit[i]]) {
			get += query(p);
			if(get >= need[shit[i]]) {
				got_it = true;
				break;
			}
		}
		if(got_it)
			shit_l[++ pl] = shit[i];
		else {
			need[shit[i]] -= get;
			shit_r[++ pr] = shit[i];
		}
	}

	with_bit(-1);

	for(int i = 1; i <= pl; i ++)
		shit[l + i - 1] = shit_l[i];
	for(int i = 1; i <= pr; i ++)
		shit[l + pl + i - 1] = shit_r[i];

	solve(l, l + pl - 1, L, mid);
	solve(l + pl, r, mid + 1, R);

}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= m; i ++)
		pos[input()].push_back(i);

	for(int i = 1; i <= n; i ++)
		need[i] = input();

	int k = input();
	for(int i = 1; i <= k; i ++) {
		boom_l[i] = input();
		boom_r[i] = input();
		boom[i] = input();
	}

	boom_l[k + 1] = 1;
	boom_r[k + 1] = m;
	boom[k + 1] = 1000000000;
	k ++;

	for(int i = 1; i <= n; i ++)
		shit[i] = i;

	solve(1, n, 1, k);

	for(int i = 1; i <= n; i ++)
		if(ans[i] == k)
			puts("NIE");
		else
			printf("%d\n", ans[i]);
}
