class Suffix_Array {
public:
    Suffix_Array(string s) {
        vector<int> p;
        vector<int> c;

        s += '$';
        int n = s.size();

        p.resize(n);
        c.resize(n);

        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { s[i], i };
        }
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }

        int k = 0;
        while ((1 << k) < n) {
            vector<int> p_new(n);
            for (int i = 0; i < n; i++) {
                p_new[i] = (p[i] - (1 << k) + n) % n;
            }

            vector<int> cnt(n);
            for (int x : c) {
                cnt[x]++;
            }

            vector<int> pos(n);
            pos[0] = 0;
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            for (int x : p_new) {
                p[pos[c[x]]++] = x;
            }

            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n] };
                pair<int, int> now = { c[p[i]], c[(p[i] + (1 << k)) % n] };

                c_new[p[i]] = c_new[p[i - 1]] + (now != prev);
            }
            c = c_new;

            k++;
        }

        suf_arr = p;
        C = c;

        LCP.resize(n - 1);

        k = 0;
        for (int i = 0; i < n - 1; i++) {
            int x = c[i];
            if (k > 0) {
                --k;
            }
            while (s[p[x - 1] + k] == s[p[x] + k]) {
                ++k;
            }
            LCP[x - 1] = k;
        }

        Build_LCP(LCP);
    }

    int lcp_query(int left, int right) {
        if (left == right) {
            return (int)LCP.size() - left + 1;
        }

        left = C[left];
        right = C[right];

        if (right < left) {
            swap(left, right);
        }

        right -= 1;

        if (left == right) {
            return a[left];
        }
        else {
            int lvl = highestBit[left ^ right];
            return Function(Stable[left][lvl], Stable[right][lvl]);
        }
    }

private:
    vector<int> suf_arr;
    vector<int> C;
    vector<int> LCP;

    int N, K;
    int neutral = 1e9;

    vector<vector<int>> Stable;
    vector<int> highestBit;
    vector<int> a;

    int Function(int left, int right) {
        return min(left, right);
    }

    void Build_LCP(const vector<int>& vec) {
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
};
