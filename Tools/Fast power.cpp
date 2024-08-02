int Fast_power_mod(int a, int n, int mod) {
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

int Fast_power(int a, int n) {
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
