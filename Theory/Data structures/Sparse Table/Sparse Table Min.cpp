class Sparse_table {
private:
    int N, K;
    vector<vector<int>> Stable;
    vector<int> LOG2;
public:
    Sparse_table(const vector<int>& vec) {
        this->N = (int)(vec.size());
        this->K = log2(N) + 2;

        LOG2.resize(N + 1);;
        for (int i = 0; i <= N; i++) {
            LOG2[i] = log2(i);
        }

        Stable.resize(N + 1);

        for (int i = 0; i < N; i++) {
            Stable[i].resize(K + 1);
            Stable[i][0] = vec[i];
        }

        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                Stable[i][j] = min(Stable[i][j - 1], Stable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        return min(Stable[l][LOG2[r - l + 1]], Stable[r - (1 << LOG2[r - l + 1]) + 1][LOG2[r - l + 1]]);
    }
};
