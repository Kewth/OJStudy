#if 0
2019.08.28

块状链表，由于数据随机，无需重构。
#endif
#include <cstdio>
#include <cmath>
#include <vector>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100500, maxb = 333;
std::vector<int> s[maxb];
int tmp[maxn];

int main() {
	int n = input(), q = n;

	int b = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		s[i / b].push_back(input());

	while(q --) {
		int typ = input(), l = input(), r = input();
		input();

		if(typ == 0) {
			l --;
			int p = 0;
			while(l > int(s[p].size()))
				l -= s[p ++].size();
			s[p].insert(s[p].begin() + l, r);
		}

		else {
			r --;
			int p = 0;
			while(r >= int(s[p].size()))
				r -= s[p ++].size();
			printf("%d\n", s[p][size_t(r)]);
		}
	}
}
