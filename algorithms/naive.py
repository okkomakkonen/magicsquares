
MAX = 200

a_and_i_same = list()


def inv(n):
    if n <= 0:
        return 0
    c = int(n**0.5)
    if c**2 == n:
        return c
    return 0


def factors(n):
    res = set()
    for i in range(1, int(n**0.5)):
        if n % i == 0:
            res.add(i)
    return res


def check_magic_square(a, b, c, d, e, f, g, h, i):
    k = a**2 + b**2 + c**2
    if d**2 + e**2 + f**2 != k:
        return False
    if g**2 + h**2 + i**2 != k:
        return False
    if a**2 + d**2 + g**2 != k:
        return False
    if b**2 + e**2 + h**2 != k:
        return False
    if c**2 + f**2 + i**2 != k:
        return False
    if a**2 + e**2 + i**2 != k:
        return False
    if c**2 + e**2 + g**2 != k:
        return False
    return True


def search_magic_squares_brute():
    for a in range(1, MAX+1):
        for b in range(1, MAX+1):
            for c in range(1, a+1):
                k = a**2 + b**2 + c**2
                for d in range(1, MAX+1):
                    g = inv(k - a**2 - d**2)
                    if g == 0:
                        continue
                    e = inv(k - g**2 - c**2)
                    if e == 0:
                        continue
                    f = inv(k - d**2 - e**2)
                    if f == 0:
                        continue
                    h = inv(k - b**2 - e**2)
                    if h == 0:
                        continue
                    i = inv(k - c**2 - f**2)
                    if i == 0:
                        continue
                    if a**2 + e**2 + i**2 != k:
                        continue
                    if g**2 + h**2 + i**2 != k:
                        continue

                    # Print the square
                    print(a, b, c)
                    print(d, e, f)
                    print(g, h, i)
                    print()

                    # Check if all are of same parity
                    # par = (n % 2 == 0 for n in [a, b, c, d, e, f, g, h, i])
                    # print(all(par) or not any(par))


def search_magic_squares_fast():

    for c in range(2, MAX+1):
        for g in range(1 if c % 2 else 2, c, 2):
            facts = factors(c**2 - g**2)
            for fact1 in facts:
                if (fact1 + (c**2 - g**2) / fact1) % 2 != 0:
                    continue
                d = ((c**2 - g**2) // fact1 + fact1) // 2
                b = ((c**2 - g**2) // fact1 - fact1) // 2
                if b % 2 != d % 2:
                    continue

                for fact2 in facts:
                    if (fact2 + (c**2 - g**2) / fact2) % 2 != 0:
                        continue
                    h = ((c**2 - g**2) // fact2 + fact2) // 2
                    f = ((c**2 - g**2) // fact2 - fact2) // 2
                    if h % 2 != f % 2 or b % 2 != f % 2:
                        continue
                    if 2*c**2 != d**2 + h**2 or 2*g**2 != b**2 + f**2:
                        continue
                    if c == d and g == b:
                        continue
                    print(' ', b, c)
                    print(d, ' ', f)
                    print(g, h, ' ')
                    print()
                    continue
                    k = b**2 + c**2 + (h**2 + f**2) / 2
                    a = inv(k - b**2 - c**2)
                    if a == 0:
                        continue
                    i = inv(k - c**2 - f**2)
                    if i == 0:
                        continue
                    e = inv(k - b**2 - h**2)
                    if e == 0:
                        continue
                    if not check_magic_square(a, b, c, d, e, f, g, h, i):
                        continue

                    print(a, b, c)
                    print(d, e, f)
                    print(g, h, i)
                    print()

                    a_and_i_same.append(a == i)


def main():
    search_magic_squares_fast()
    print(all(a_and_i_same))


main()
