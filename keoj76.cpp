#if 0
2019.10.05

刷新三观系列，埃氏筛竟然可以跑这么快。。
#endif
#include <cstdio>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline unsigned uinput() { unsigned x; scanf("%u", &x); return x; }

const int maxn = 100000005;
std::bitset<maxn> nop;

int main() {
	size_t n = uinput();
	for(size_t i = 2; i <= n; i ++)
		if(!nop[i]) {
			printf("%lu\n", i);
			if(i <= n / i)
				for(size_t j = i * i; j <= n; j += i)
					nop[j] = 1;
		}
}
