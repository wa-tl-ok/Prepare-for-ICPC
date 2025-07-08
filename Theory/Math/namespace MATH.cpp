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

    struct Int {
        int value;
        static const int mod = 998244353;

        Int() : value(0) {}

        Int(int value) : value(normalize(value)) {}

        Int(const Int& other) : value(other.value) {}

        static int normalize(int x) {
            if (x < 0) {
                x += mod;
            }
            return x % mod;
        }

        Int operator+(const Int& other) const {
            return Int(value + other.value);
        }

        Int operator-(const Int& other) const {
            return Int(value - other.value);
        }

        Int operator*(const Int& other) const {
            return Int(static_cast<int>(1LL * value * other.value % mod));
        }

        Int operator/(const Int& other) const {
            return *this * other.inv();
        }

        Int pow(int exp) const {
            Int result(1);
            Int base(*this);
            while (exp > 0) {
                if (exp % 2 == 1) {
                    result *= base;
                }
                base *= base;
                exp /= 2;
            }
            return result;
        }

        Int inv() const {
            return pow(mod - 2);
        }

        Int& operator=(int newValue) {
            value = normalize(newValue);
            return *this;
        }

        Int& operator+=(const Int& other) {
            value = normalize(value + other.value);
            return *this;
        }

        Int& operator-=(const Int& other) {
            value = normalize(value - other.value);
            return *this;
        }

        Int& operator*=(const Int& other) {
            value = normalize(static_cast<int>(1LL * value * other.value % mod));
            return *this;
        }

        Int& operator/=(const Int& other) {
            return *this *= other.inv();
        }

        friend std::ostream& operator<<(std::ostream& os, const Int& obj) {
            os << obj.value;
            return os;
        }
    };

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

    class Matrix {
    public:
        Matrix(const vector<vector<int>>& matrix) : data(matrix) {}

        vector<vector<int>> getData() const {
            return data;
        }

        Matrix rotateclockwise() const {
            vector<vector<int>> rotated_matrix(data[0].size(), vector<int>(data.size(), 0));
            for (size_t i = 0; i < data.size(); ++i) {
                for (size_t j = 0; j < data[0].size(); ++j) {
                    rotated_matrix[j][data.size() - 1 - i] = data[i][j];
                }
            }
            return Matrix(rotated_matrix);
        }

        Matrix operator+(const Matrix& other) const {
            if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
                throw invalid_argument("Matrices dimensions do not match for addition.");
            }

            vector<vector<int>> result_matrix(data.size(), vector<int>(data[0].size(), 0));
            for (size_t i = 0; i < data.size(); ++i) {
                for (size_t j = 0; j < data[0].size(); ++j) {
                    result_matrix[i][j] = data[i][j] + other.data[i][j];
                }
            }

            return Matrix(result_matrix);
        }

        Matrix operator-(const Matrix& other) const {
            if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
                throw invalid_argument("Matrices dimensions do not match for subtraction.");
            }

            vector<vector<int>> result_matrix(data.size(), vector<int>(data[0].size(), 0));
            for (size_t i = 0; i < data.size(); ++i) {
                for (size_t j = 0; j < data[0].size(); ++j) {
                    result_matrix[i][j] = data[i][j] - other.data[i][j];
                }
            }

            return Matrix(result_matrix);
        }

        Matrix operator*(const Matrix& other) const {
            size_t rows1 = data.size();
            size_t columns1 = data[0].size();
            size_t rows2 = other.data.size();
            size_t columns2 = other.data[0].size();

            if (columns1 != rows2) {
                throw invalid_argument("Matrices dimensions do not match for multiplication.");
            }

            vector<vector<int>> result_matrix(rows1, vector<int>(columns2, 0));
            for (size_t i = 0; i < rows1; ++i) {
                for (size_t j = 0; j < columns2; ++j) {
                    for (size_t k = 0; k < columns1; ++k) {
                        result_matrix[i][j] += data[i][k] * other.data[k][j];
                    }
                }
            }

            return Matrix(result_matrix);
        }

        bool operator==(const Matrix& other) const {
            return data == other.data;
        }

        bool operator!=(const Matrix& other) const {
            return !(*this == other);
        }

        Matrix pow(int n) const {
            if (data.size() != data[0].size()) {
                throw invalid_argument("Matrix must be square for exponentiation.");
            }

            Matrix result = identity(data.size());
            Matrix base = *this;

            while (n > 0) {
                if (n % 2 == 1) {
                    result = result * base;
                }
                base = base * base;
                n /= 2;
            }

            return result;
        }

        void print() const {
            for (const auto& row : data) {
                for (const auto& elem : row) {
                    cout << elem << " ";
                }
                cout << endl;
            }
        }

    private:
        vector<vector<int>> data;

        static Matrix identity(size_t size) {
            vector<vector<int>> identity_matrix(size, vector<int>(size, 0));
            for (size_t i = 0; i < size; ++i) {
                identity_matrix[i][i] = 1;
            }
            return Matrix(identity_matrix);
        }
    };
}
