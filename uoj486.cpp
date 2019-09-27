#if 0
2019.09.15

称 1 到 k 的链为主链，主链有一个性质就是可以认为相邻两点 x, y 和非主链点 z 之间一定有蓝边。
否则如果全是红边，就可以通过 x-z-y 使得主链扩展，点数 +1 从而构成长 k + 1 的红路达到要求。
另外一个性质是可以认为 1 和 k 与其他非主链点都连蓝边，原因类似。

称主链上的点为红点，非主链点为蓝点，一个红蓝点交错且由蓝边连接且端点蓝点的链为交错路。
考虑维护两条交错路，一开始都只有一个蓝点。
每次在 2 ~ k - 1 中拿出相邻的两个红点，
再随便选一个蓝点考虑把这个蓝点通过两个红点加到交错路里。
假设红点先用完，把交错路的端点通过 1, k 连接成一个环。
此时环上有 k / 2 + 1 个红点和 k / 2 + 1 个蓝点，一定可以选出一条长为 k + 1 的蓝路。
如果蓝点先用完，同样连接成环，此时一定还有相邻红点，拿来连蓝点使长度加 1 。

那么现在的问题就是扩展交错路。
假设当前拿出了红点 x, y 和蓝点 z ，两个交错路的端点是 a, b 。
先检验 x, y 与 z 的连边，然后分类讨论，再检验 a, b 与 x, y 的连边即可。
这样需要 6 次询问，但是控制好检验顺序及时去掉不必要的检验可以在 4 次询问内增广。
过程中出现不满足上述性质时直接输出红路退出。
#endif
#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
#if 0 // graph.h
#ifndef graph_h
#define graph_h

#include<vector>
#include<stdio.h>

bool query(int a, int b);
std::vector<int> find_longer_path(int n, int k);

#endif
#else
# include "graph.h"
#endif
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

std::vector<int> red_path(int x, int y, int z, int k) {
	std::vector<int> res;
	for(int i = 1; i <= x; i ++)
		res.push_back(i);
	res.push_back(z);
	for(int i = y; i <= k; i ++)
		res.push_back(i);
	assert(int(res.size()) == k + 1);
	return res;
}

std::vector<int> find_longer_path(int n, int k) {
	std::vector<int> res;
	std::stack<int> a, b;
	int z = k;
	a.push(++ z);
	b.push(++ z);

	auto link_by = [&](int x) {
		a.push(x);
		while(not b.empty()) {
			a.push(b.top());
			b.pop();
		}
		b.push(z);
	};

	for(int x = 2; x < k - 1 and z < n; x += 2) {
		int y = x + 1;
		z ++;
		int q1 = query(a.top(), x);
		int q2 = query(b.top(), x);

		if(q1 and q2) {
			if(query(a.top(), y))
				return red_path(x, y, a.top(), k);
			if(query(b.top(), y))
				return red_path(x, y, b.top(), k);
			link_by(y);
		}

		else if(!q1 and !q2)
			link_by(x);

		else {
			if(q2)
				std::swap(a, b);
			if(!query(z, y)) {
				if(query(a.top(), y))
					return red_path(x, y, a.top(), k);
				a.push(y);
				a.push(z);
			} else if(query(z, x))
				return red_path(x, y, z, k);
			else {
				b.push(x);
				b.push(z);
			}
		}
	}

	if(query(1, a.top()))
		return red_path(0, 1, a.top(), k);
	if(query(1, b.top()))
		return red_path(0, 1, b.top(), k);

	link_by(1);
	while(not a.empty()) {
		res.push_back(a.top());
		a.pop();
	}

	assert(int(res.size()) <= k + 1);

	if(int(res.size()) >= k + 1)
		return res;

	if(query(k, res[res.size() - 1]))
		return red_path(k, k + 1, res[res.size() - 1], k);
	res.push_back(k);

	if(int(res.size()) < k + 1) {
		int x = k - 2, y = k - 1;
		if(not query(x, res[0]))
			res.insert(res.begin(), x);
		else if(not query(y, res[0]))
			res.insert(res.begin(), y);
		else
			return red_path(x, y, res[0], k);
	}

	assert(int(res.size()) == k + 1);
	return res;
}
