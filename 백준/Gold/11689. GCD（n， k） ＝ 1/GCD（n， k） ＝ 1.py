n = int(input())
res = n
for i in range(2, round(n ** 0.5) + 1):
	if n % i == 0:
		while n % i == 0:
			n //= i
		res *= 1 - (1 / i)
if n > 1:
	res *= 1 - (1 / n)
print(round(res))