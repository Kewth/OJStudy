#if 0
2020.05.23

  注意到右端点的移动只会使得字典序增大，而且由于每次操作后长度增加，事实上确定移动的左端
点后右端点可以移动到任意位置，因此可以忽略右端点的移动。
  那么问题转换为对于每个 k ，把所有以 k 为结尾的子串拿出来游戏，每次只能从字典序大的走到
字典序小的，那么先手如果有操作，直接移动到字典序最小的串即可，也就是说先手必败当且仅当 k
就是所有串中字典序最小的串，由于该串大小为 1 ，这个命题等价于没有其他串的开头字母比 k 小。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 500005;
char s[maxn];

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	int min = 256;
	for (int i = 1; i <= n; i ++)
		if (s[i] <= min) {
			puts("Mike");
			min = s[i];
		} else
			puts("Ann");
}
