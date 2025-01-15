class P_Func {
public:
    P_Func(string s) {
        S = s;
        N = S.size();

        pfunc.resize(N + 1);
        pfunc[0] = -1;
    }

    void build() {
        for (int i = 1; i <= N; i++) {
            int k = pfunc[i - 1];

            while (k != -1 && S[k] != S[i - 1]) {
                k = pfunc[k];
            }

            pfunc[i] = k + 1;
        }
    }

    void print() {
        for (int i = 1; i <= N; i++) {
            cout << pfunc[i] << ' ';
        }
    }

private:
    string S;
    int N;

    vector<int> pfunc;
};
