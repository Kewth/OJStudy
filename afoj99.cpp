#if 0
2019.08.21

大型模拟现场。
#endif
#include <cstdio>
#include <numeric>
#include <cstring>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int tot[50];

bool check(int last, int d) {
	if(d == 0) {
		int pair = 0;

		for(int i = 11; i <= 47; i ++)
			if(tot[i] >= 2)
				pair ++;

		/* debug("%d pair\n", pair); */

		if(not pair) return false;
		if(pair == 7) return true;

		int country_no_double[15], p = 0;

		for(int i = 41; i <= 47; i ++)
			country_no_double[++ p] = tot[i];
		for(int i = 10; i <= 30; i += 10) {
			country_no_double[++ p] = tot[i + 1];
			country_no_double[++ p] = tot[i + 9];
		}

		int sum = 0;

		for(int i = 1; i <= p; i ++) {
			sum += country_no_double[i];
			if(country_no_double[i] != 1 and country_no_double[i] != 2)
				sum = - 10000;
		}

		/* debug("sum %d\n", sum); */

		if(sum == 14) return true;

		for(int i = 11; i <= 47; i ++)
			if(tot[i] >= 2) {
				tot[i] -= 2;
				bool c = check(11, d + 1);
				tot[i] += 2;
				if(c) return true;
			}

		return false;
	}

	if(d == 5)
		return true;

	for(int i = last; i <= 47; i ++)
		if(i % 10) {
			if(tot[i] >= 3) {
				tot[i] -= 3;
				bool c = check(i, d + 1);
				tot[i] += 3;
				if(c) return true;
			}

			if(i < 40 and i % 10 >= 3 and tot[i] and tot[i - 1] and tot[i - 2]) {
				tot[i] --;
				tot[i - 1] --;
				tot[i - 2] --;
				bool c = check(i, d + 1);
				tot[i] ++;
				tot[i - 1] ++;
				tot[i - 2] ++;
				if(c) return true;
			}
	}

	return false;
}

int main() {
	int T = input();

	while(T --) {
		char s[15][5];

		memset(tot, 0, sizeof tot);

		for(int i = 1; i <= 13; i ++) {
			scanf("%s", s[i]);

			if(s[i][1] == 'm')
				tot[10 + *s[i] - '0'] ++;
			if(s[i][1] == 's')
				tot[20 + *s[i] - '0'] ++;
			if(s[i][1] == 'p')
				tot[30 + *s[i] - '0'] ++;
			if(s[i][1] == 'c')
				tot[40 + *s[i] - '0'] ++;
		}

		char typ[6] = "0mspc";
		std::vector<int> ans;

		for(int i = 11; i <= 47; i ++)
			if(i % 10 and tot[i] < 4) {
				/* debug("try %d%c\n", i % 10, typ[i / 10]); */

				tot[i] ++;
				if(check(0, 0))
					ans.push_back(i);
				tot[i] --;

				/* for(int j = 11; j <= 47; j ++) */
				/* 	if(tot[j]) */
				/* 		debug("have %d%c (%d)\n", j % 10, typ[j / 10], tot[j]); */
			}

		if(ans.empty())
			puts("Nooten");
		else {
			printf("%lu", ans.size());
			for(size_t i = 0; i < ans.size(); i ++)
				printf(" %d%c", ans[i] % 10, typ[ans[i] / 10]);
			puts("");
		}
	}
}
