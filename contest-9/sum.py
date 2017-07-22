n = int(input())
ans = 0
if n <= 0:
 for i in range(1, n - 1, -1):
  ans += i
else:
 for i in range(1, n + 1):
  ans += i
print(ans)
