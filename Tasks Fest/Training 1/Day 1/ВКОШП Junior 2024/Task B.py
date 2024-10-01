import math

def gcd(a, b):
    if a > b:
        a, b = b, a
    while a != 0:
        b = b % a
        if a > b:
            a, b = b, a
    return b

def solve():
    a, b, n = map(int, input().split())
    s = a * b // gcd(a, b)
    f = s + n
    print(2 + (f - s) // a + (f - s) // b)

def main():
    multitest = False
    if multitest:
        ctt = int(input())
        for _ in range(ctt):
            solve()
    else:
        solve()

if __name__ == "__main__":
    main()
