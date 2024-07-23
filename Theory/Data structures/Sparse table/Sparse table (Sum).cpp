class Sparse_table_sum {
private:
    int N, K;
    vector<vector<int>> Stable;

public:
    Sparse_table_sum(const vector<int>& vec) {
        this->N = (int)vec.size();
        this->K = log2(N) + 2;

        Stable.resize(N + 1);

        for (int i = 0; i < N; i++) {
            Stable[i].resize(K + 1);
            Stable[i][0] = vec[i];
        }

        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                Stable[i][j] = Stable[i][j - 1] + Stable[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int l, int r) {
        int sum = 0;
        int sz = r - l + 1;

        for (int k = K; k >= 0; k--) {
            if (sz >= (1 << k)) {
                sum += Stable[l][k];
                sz -= 1 << k;
                l += 1 << k;
            }
        }

        return sum;
    }
};
