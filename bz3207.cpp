#if 0
2019.03.13

这题出现在主席树的计划里。
我一看，卧槽这不莫队 + 哈希嘛。
根号复杂度有点卡，unordered_map + 排序优化即可。
#endif
#include <bits/stdc++.h>

int input() {
	int res = 0, ch = getchar();
	while(ch < '0' or ch > '9') ch = getchar();
	while(ch >= '0' and ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res;
}

/* typedef __uint128_t Hash; */
typedef unsigned long long Hash;
struct ask {
	int l, r, id;
	int fuck;
	Hash hash;
};

/* const Hash base = 1000000007; */
const Hash base = 100;
const int maxn = 100050;
int num[maxn];
Hash hh[maxn];
ask sk[maxn];
bool ans[maxn];
int block;

void output(Hash x, bool first = true) {
	if(first and not x)
		std::clog << '0' << std::endl;
	if(not x) return;
	output(x / 10, false);
	std::clog << char('0' + (x % 10));
	if(first)
		std::clog << std::endl;
}

std::unordered_map<Hash, int> mp;
/* #define add(x) mp[hh[x]] ++ */
/* #define remove(x) mp[hh[x]] -- */
inline void add(int x) {
	/* std::clog << "add "; */
	/* output(hh[x]); */
	mp[hh[x]] ++;
}
inline void remove(int x) {
	/* std::clog << "remove "; */
	/* output(hh[x]); */
	mp[hh[x]] --;
}

bool cmp(ask a, ask b) {
	assert(block);
	int al = a.l / block, bl = b.l / block;
	if(al == bl)
		return (al & 1) ? a.r < b.r : a.r > b.r;
		/* return a.r < b.r; */
	return al < bl;
}

int main() {
	int n = input(), q = input(), m = input();
	Hash power = 1;
	for(int i = 1; i <= m; i ++)
		power *= base;
	for(int i = 1; i <= n; i ++) {
		hh[i] = hh[i - 1] * base;
		hh[i] += Hash(num[i] = input());
		if(i > m)
			hh[i] -= Hash(num[i - m]) * power;
	}
	for(int i = 1; i <= q; i ++) {
		sk[i].l = input() + m - 1;
		sk[i].r = input();
		Hash &now = sk[i].hash;
		now = 0;
		for(int tmp = m; tmp --;)
			(now *= base) += unsigned(input());
		/* output(now); */
		sk[i].id = i;
	}
	for(int i = m; i <= n; i ++)
		/* output(hh[i]); */
	block = int(sqrt(n));
	std::sort(sk + 1, sk + q + 1, cmp);
	int l = m, r = m - 1;
	for(int i = 1; i <= q; i ++) {
		assert(sk[i].id >= 1);
		assert(sk[i].id <= q);
		if(sk[i].l > sk[i].r) {
			ans[sk[i].id] = false;
			continue;
		}
		while(l > sk[i].l) add(-- l);
		while(r < sk[i].r) add(++ r);
		while(l < sk[i].l) remove(l ++);
		while(r > sk[i].r) remove(r --);
		ans[sk[i].id] = mp[sk[i].hash];
		/* std::clog << "got ans " << sk[i].id << " hash:" */
		/* 	<< sk[i].hash << ' ' << mp[sk[i].hash] << std::endl; */
	}
	for(int i = 1; i <= q; i ++)
		if(ans[i])
			puts("No");
		else
			puts("Yes");
}
