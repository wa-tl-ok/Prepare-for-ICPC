bool MR(int n) {
    for (int test = 0; test < 5; ++test) {
        int a = randomabint(2, n - 2);
        int s = 0;
        int d = n - 1;
        while (d % 2 == 0) {
            s += 1;
            d /= 2;
        }
        int x = Fast_power_mod(a, d, n);
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
