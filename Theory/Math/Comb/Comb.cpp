struct Comb {
    static std::vector<Int> fact;
    static std::vector<Int> inv_fact;
    static int max_n;

    static void ensure(int n) {
        if (max_n >= n) {
            return;
        }

        if (max_n == -1) {
            fact = { Int(1) };
            inv_fact = { Int(1) };
            max_n = 0;
            if (n == 0) {
                return;
            }
        }

        fact.resize(n + 1);
        for (int i = max_n + 1; i <= n; i++) {
            fact[i] = fact[i - 1] * Int(i);
        }

        inv_fact.resize(n + 1);
        inv_fact[n] = fact[n].inv();
        for (int i = n - 1; i > max_n; i--) {
            inv_fact[i] = inv_fact[i + 1] * Int(i + 1);
        }

        max_n = n;
    }

    static Int factorial(int n) {
        if (n < 0) {
            return Int(0);
        }
        ensure(n);
        return fact[n];
    }

    static Int inv_factorial(int n) {
        if (n < 0) {
            return Int(0);
        }
        ensure(n);
        return inv_fact[n];
    }

    // C(n, k)
    static Int comb(int n, int k) {
        if (k < 0 || k > n) {
            return Int(0);
        }
        ensure(n);
        return fact[n] * inv_fact[k] * inv_fact[n - k];
    }

    // P(n, k) = n! / (n-k)!
    static Int perm(int n, int k) {
        if (k < 0 || k > n) {
            return Int(0);
        }
        ensure(n);
        return fact[n] * inv_fact[n - k];
    }
};

std::vector<Int> Comb::fact = {};
std::vector<Int> Comb::inv_fact = {};
int Comb::max_n = -1;
