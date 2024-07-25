class Sparse_table_min {
private:
    int N, K;
    vector<vector<int>> Stable;
public:
    Sparse_table_min(const vector<int>& vec) {
        vector<int> new_vec;
        for (auto p : vec) {
            new_vec.push_back(p);
        }

        this->K = 0;

        int n = (int)vec.size();
        int p = 1;
        while (p < n) {
            p *= 2;
            ++(this->K);
        }

        for (int i = 0; i < p - n; i++) {
            new_vec.push_back(INT_MAX);
        }

        this->N = (int)new_vec.size();

        Stable.resize(N);

        for (int i = 0; i < N; i++) {
            Stable[i].resize(K);
            Stable[i][0] = new_vec[i];
        }

        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                Stable[i][j] = min(Stable[i][j - 1], Stable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int mn = INT_MAX;
        int sz = r - l + 1;

        for (int k = K; k >= 0; k--) {
            if (sz >= (1 << k)) {
                mn = min(mn, Stable[l][k]);
                sz -= (1 << k);
                l += (1 << k);
            }
        }

        return mn;
    }
};
