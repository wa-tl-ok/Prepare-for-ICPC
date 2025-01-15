class Z_Func {
public:
    Z_Func(string s) {
        S = s;
        N = S.size();

        zfunc.resize(N);
        zfunc[0] = N;
    }

    void build() {
        int L = 0;
        int R = 0;

        for (int i = 1; i < N; i++) {
            zfunc[i] = max(0LL, min(R - i, zfunc[i - L]));

            while (i + zfunc[i] < N && S[zfunc[i]] == S[i + zfunc[i]]) {
                ++zfunc[i];
            }

            if (i + zfunc[i] > R) {
                L = i;
                R = i + zfunc[i];
            }
        }
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << zfunc[i] << ' ';
        }
    }

private:
    string S;
    int N;

    vector<int> zfunc;
};
