#!/bin/python3
# O((N+4)^4) without precision error

from fractions import Fraction

def subtract(a, b):
    return (a[0]-b[0], a[1]-b[1])
def add(a, b):
    return (a[0]+b[0], a[1]+b[1])
def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]
def dot(a, b):
    return a[0] * b[0] + a[1] * b[1]
def collinear(a, b, c):
    ab = subtract(b, a)
    ac = subtract(c, a)
    return cross(ab, ac) == Fraction(0, 1)
def dist2(a, b):
    ab = subtract(b, a)
    return dot(ab, ab)
def circumCenter(a, b, c):
    bb = subtract(b, a)
    cc = subtract(c, a)
    db = dot(bb, bb)
    dc = dot(cc, cc)
    d = 2 * cross(bb, cc)
    return subtract(a, ((bb[1]*dc-cc[1]*db)/d, (cc[0]*db-bb[0]*dc)/d))

if __name__ == "__main__":
    n, m = map(int, input().split())
    points = [(Fraction(0, 1), Fraction(0, 1)) for i in range(n+m)]
    for i in range(n):
        x, y = map(int, input().split())
        points[i] = (Fraction(x, 1), Fraction(y, 1))
    for i in range(m):
        x, y = map(int, input().split())
        points[i+n] = (Fraction(x, 1), Fraction(y, 1))
    s = n+m;
    ans = min(n, m)
    for i in range(s):
        for j in range(i+1, s):
            for k in range(j+1, s):
                if collinear(points[i], points[j],points[k]):
                    continue
                center = circumCenter(points[i], points[j], points[k])
                r2 = dist2(center, points[i])
                cur = 0
                for l in range(s):
                    if ((l == i) or (l == j) or (l == k)):
                        continue
                    d = dist2(center, points[l])
                    if l < n:
                        cur += d > r2
                    else:
                        cur += d < r2
                ans = min(ans, cur)
    for i in range(s):
        for j in range(i+1, s):
            center = add(points[i], points[j])
            center = (center[0]/2, center[1]/2)
            r2 = dist2(center, points[i])
            cur = 0
            for l in range(s):
                if ((l == i) or (l == j)):
                    continue
                d = dist2(center, points[l])
                if l < n:
                    cur += d > r2
                else:
                    cur += d < r2
            ans = min(ans, cur)
    print(ans)