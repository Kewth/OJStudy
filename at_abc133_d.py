n = int(input())
A = [int(i) for i in input().split()]
assert len(A) == n
S = sum(A)
ans = S
for i in range(1, n, 2):
    ans -= A[i] * 2
print(ans, end=' ')
for i in range(1, n):
    ans = A[i - 1] * 2 - ans
    print(ans, end=' ')
print()
