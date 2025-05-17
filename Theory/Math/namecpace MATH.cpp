namespace MATH {
    int randomabint(int a, int b) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(a, b);
        return distrib(gen);
    }

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b; b = a % b; a = temp;
        }
        return a;
    }

    int gcd_array(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) {
            return 0;
        }
        int result = arr[0];
        FOR(i, 1, n - 1) {
            result = gcd(result, arr[i]);
            if (result == 1) {
                break;
            }
        }
        return result;
    }

    int lcm(int a, int b) {
        if ((int)(a) * (b / gcd(a, b)) > 2e18) {
            return (int)2e18;
        }
        else {
            return (a) * (b / gcd(a, b));
        }
    }

    int lcm_array(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) {
            return 0;
        }
        double result = arr[0];
        for (int i = 1; i < n; ++i) {
            result = lcm((int)result, arr[i]);
            if (result >= 2e18) {
                return (int)2e18;
            }
        }
        return (int)result;
    }

    int fast_power_mod(int a, int n, int mod) {
        if (n == 0) {
            return 1;
        }
        int result = 1;
        int base = a;
        while (n > 0) {
            if (n % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            n = n / 2;
        }
        return result % mod;
    }

    int fast_power(int a, int n) {
        if (n == 0) {
            return 1;
        }
        int result = 1;
        int base = a;
        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n = n / 2;
        }
        return result;
    }

    int safe_pow(int a, int b) {
        int p = 1;
        for (int i = 0; i < b; i++) {
            double q = p;
            q *= a;
            if (q > 2e18) {
                return 2e18;
            }
            p *= a;
        }
        return p;
    }

    bool check_for_prime(int n) {
        assert(n > 0);
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    bool mr_check_for_prime(int n) {
        assert(n > 0);
        if (n == 1) {
            return false;
        }
        if (n == 2 || n == 3) {
            return true;
        }
        for (int test = 0; test < 10; ++test) {
            int a = randomabint(2, n - 2);
            int s = 0;
            int d = n - 1;
            while (d % 2 == 0) {
                s += 1;
                d /= 2;
            }
            int x = fast_power_mod(a, d, n);
            if (x != 1 && x != n - 1) {
                int F = 0;
                for (int i = 0; i < s - 1; ++i) {
                    x = (x * x) % n;
                    if (x == n - 1) {
                        F = 1;
                        break;
                    }
                }
                if (F == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    int bs_ll(vector<int>& arr, int target) {
        /*
            Find max index of number in arr that < target
        */
        if (arr[0] >= target) {
            return -1;
        }
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (arr[mid] >= target) {
                right = mid - 1;
            }
            else {
                if (arr[mid + 1] >= target) {
                    return mid;
                }
                left = mid + 1;
            }
        }
        return left;
    }

    int bs_rl(vector<int>& arr, int target) {
        /*
            Find min index of number that >= target
        */
        if (arr[arr.size() - 1] < target) {
            return -1;
        }
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }

    int bs_lr(vector<int>& arr, int target) {
        /*
            Find max index of number that <= target
        */
        if (arr[0] > target) {
            return -1;
        }
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return right;
    }

    int bs_rr(vector<int>& arr, int target) {
        /*
            Find min index of number that > target
        */
        if (arr[arr.size() - 1] <= target) {
            return -1;
        }
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] <= target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }

    vector<int> sieve_of_eratosthenes(int n) {
        if (n < 2) return {};

        vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;

        for (int p = 2; p * p <= n; ++p) {
            if (is_prime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    is_prime[i] = false;
                }
            }
        }

        vector<int> primes;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }

        return primes;
    }
}
