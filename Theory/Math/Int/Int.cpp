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
