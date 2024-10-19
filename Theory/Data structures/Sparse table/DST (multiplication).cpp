class DST {
private:
    int N, K;
    int neutral = 1;

    vector<vector<int>> Stable;
    vector<int> highestBit;
    vector<int> a;

    int Function(int left, int right) {
        return (left * right);
    }
public:
    DST(const vector<int>& vec) {
        for (auto p : vec) {
            a.push_back(p);
        }

        this->K = 0;

        int n = (int)vec.size();
        int p = 1;
        while (p < n) {
            p <<= 1;
            ++(this->K);
        }

        for (int i = 0; i < p - n; i++) {
            a.push_back(neutral);
        }

        this->N = (int)a.size();

        highestBit.resize(N);
        highestBit[0] = 0;
        highestBit[1] = 0;
        for (int i = 2; i < N; i++) {
            highestBit[i] = highestBit[i >> 1] + 1;
        }

        Stable.resize(N);
        for (int i = 0; i < N; i++) {
            Stable[i].resize(K);
            Stable[i][0] = a[i];
        }

        int sz = 1;
        for (int lvl = 1; lvl < K; lvl++) {
            sz = sz <<= 1;
            for (int c = sz; c < N; c += sz << 1) {
                Stable[c][lvl] = a[c];
                for (int i = c + 1; i < c + sz; i++) {
                    Stable[i][lvl] = Function(Stable[i - 1][lvl], a[i]);
                }

                Stable[c - 1][lvl] = a[c - 1];
                for (int i = c - 2; i >= c - sz; i--) {
                    Stable[i][lvl] = Function(a[i], Stable[i + 1][lvl]);
                }
            }
        }
    }

    int query(int left, int right) {
        if (left == right) {
            return a[left];
        }
        else {
            int lvl = highestBit[left ^ right];
            return Function(Stable[left][lvl], Stable[right][lvl]);
        }
    }
};
