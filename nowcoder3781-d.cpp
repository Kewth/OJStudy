#if 0
2020.01.10

显然可以枚举一个分界线，然后只要知道每个前缀的最大回文子串和每个后缀的最大回文子串。
两者的求法是本质相同的，对于前者，只需要 manacher 求出所有极大回文子串，
每个极大回文子串对应于一个区间，做前缀最大值的同时只需要考虑以当前位置为右端点的回文子串，
也就是跨过当前位置的区间的求一个最靠前的中点。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 400005;
char s[maxn], t[maxn];
int h[maxn];

void manacher(int n) {
	int mid = 0, r = 0;
	for(int i = 1; i <= n; i ++) {
		if(i > r) {
			r = i;
			mid = i;
		}
		h[i] = std::min(h[mid - (i - mid)], r - i);
		while(i - h[i] - 1 >= 0 and i + h[i] + 1 <= n and s[i - h[i] - 1] == s[i + h[i] + 1])
			h[i] ++;
		if(i + h[i] > r) {
			r = i + h[i];
			mid = i;
		}
	}
}

int max[2][maxn];
std::vector<int> erase[maxn];

void solve(int n, int o) {
	std::set<int> set;
	for(int i = 0; i <= n; i ++) {
		int l = i - h[i] + 1, r = i + h[i] - 1;
		if(l <= r) {
			set.insert(i);
			erase[r].push_back(i);
		}
	}
	int pass = 0;
	for(int i = 0; i <= n; i ++) {
		for(int x : erase[i]) {
			pass = std::max(pass, (i - x) * 2 + 1);
			set.erase(x);
		}
		erase[i].clear();
		max[o][i] = pass;
		if(!set.empty())
			max[o][i] = std::max(max[o][i], (i - *set.begin()) * 2 + 1);
	}
}

int main() {
	scanf("%s", t + 1);
	int n = int(strlen(t + 1));
	s[0] = '#';
	for(int i = 1; i <= n; i ++) {
		s[i * 2 - 1] = t[i];
		s[i * 2] = '#';
	}
	manacher(n << 1);

	solve(n << 1, 0);
	std::reverse(s, s + n * 2 + 1);
	std::reverse(h, h + n * 2 + 1);
	solve(n << 1, 1);
	std::reverse(max[1], max[1] + n * 2 + 1);

	int ans = 0;
	for(int i = 2; i < n * 2; i += 2)
		ans = std::max(ans, (max[0][i - 1] + 1) / 2 + (max[1][i + 1] + 1) / 2);
	printf("%d\n", ans);
}
