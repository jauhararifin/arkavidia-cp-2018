def pxor(x):
	if x % 4 == 1:
		return 1
	elif x % 4 == 2:
		return x + 1
	elif x % 4 == 3:
		return 0
	else:
		return x

t = int(input())
for i in range(t):
	l, r = [int(x) for x in input().split(' ')]
	print(pxor(r) ^ pxor(l-1))