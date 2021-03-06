'''
2019.04.02

卡特兰数结论题，
S(n) 就是 n 个点的不同二叉树的个数。
设 f(n) 表示 n 个点的所有不同二叉树的叶子节点和，
可以证明 f(n) = n * S(n - 1) ：

- 一个 n - 1 个点的二叉树有 n 个加点的方案得到 n 个点的二叉树，
- 一个 n 个点的二叉树可以被 k 个 n - 1 个点的二叉树得到， k 为叶子个数。
'''
n = int(input())
print('{:.9f}'.format(n * (n + 1) / (n * 4 - 2)))
