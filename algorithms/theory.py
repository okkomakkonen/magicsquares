"""Research theory of 3x3 magic squares
"""
N = 1000


def factors(n):
    assert n > 0
    for f in range(1, n + 1):
        if n % f == 0:
            yield f


def inv(n):
    c = int(n**0.5)
    if c**2 == n:
        return c
    return 0


def print_sq(a=' ', b=' ', c=' ', d=' ', e=' ', f=' ', g=' ', h=' ', i=' '):
    print(a, b, c)
    print(d, e, f)
    print(g, h, i)
    print()


def check_sq(a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0):
    s = set([
        a**2 + b**2 + c**2,
        d**2 + e**2 + f**2,
        g**2 + h**2 + i**2,
        a**2 + d**2 + g**2,
        b**2 + e**2 + h**2,
        c**2 + f**2 + i**2,
        a**2 + e**2 + i**2,
        c**2 + e**2 + g**2
    ])
    return len(s) == 1


def check(b, c, d, f, g, h):
    # s1 = set([
    #     a**2 + b**2 + c**2,
    #     a**2 + d**2 + g**2,
    #     c**2 + f**2 + i**2,
    #     g**2 + h**2 + i**2
    # ])

    s2 = set([
        # a**2 + i**2,
        d**2 + f**2,
        b**2 + h**2,
        c**2 + g**2
    ])
    return len(s2) == 1


def find():
    for c in range(2, N + 1):
        for g in range(1 if c % 2 else 2, c, 2):

            for p in factors(c**2 - g**2):
                if ((c**2 - g**2) // p + p) % 2 != 0:
                    continue
                if (c**2 - g**2) // p - p <= 0:
                    break
                h = ((c**2 - g**2) // p + p) // 2
                f = ((c**2 - g**2) // p - p) // 2

                if h % 2 != f % 2:
                    continue

                for q in factors(c**2 - g**2):
                    if (c**2 - g**2)/q - q <= 0:
                        break
                    if ((c**2 - g**2)/q + q) % 2 != 0:
                        continue
                    if 4*(c**2 + g**2) != ((c**2 - g**2) // p)**2 + ((c**2 - g**2) // q)**2 + p**2 + q**2:
                        continue
                    d = ((c**2 - g**2) // q + q) // 2
                    b = ((c**2 - g**2) // q - q) // 2

                    if d % 2 != b % 2:
                        continue

                    if d % 2 != h % 2:
                        continue

                    a = inv((f**2 + h**2) // 2)
                    if a == 0:
                        continue

                    i = inv((b**2 + d**2) // 2)
                    if i == 0:
                        continue

                    k = a**2 + b**2 + c**2

                    e = inv(k - b**2 - h**2)
                    if e == 0:
                        continue

                    if not check_sq(a, b, c, d, e, f, g, h, i):
                        continue

                    # print_sq(a, b, c, d, e, f, g, h, i)
                    yield p == q


print(all(find()))
