int BLOCK_SIZE = 1000;

class Mo {
public:
    struct QUERY {
        int l;
        int r;
        int id;

        bool operator<(const QUERY& other) const {
            int block1 = l / BLOCK_SIZE;
            int block2 = other.l / BLOCK_SIZE;

            if (block1 != block2) {
                return block1 < block2;
            }

            if (block1 % 2 == 1) {
                return r < other.r;
            }
            else {
                return r > other.r;
            }
        }
    };





    // --- STATE --- //

    map<int, int> cnt;
    int z = 0;

    void ADD(int G) {
        cnt[a[G]] += 1;

        if (cnt[a[G]] == 0) {
            // no changes
        }
        else if (cnt[a[G]] == 1) {
            ++z;
        }
        else if (cnt[a[G]] == 2) {
            --z;
        }
        else {
            // no changes
        }
    }

    void REM(int G) {
        cnt[a[G]] -= 1;

        if (cnt[a[G]] == 0) {
            --z;
        }
        else if (cnt[a[G]] == 1) {
            ++z;
        }
        else if (cnt[a[G]] == 2) {
            // no changes
        }
        else {
            // no changes
        }
    }

    void add_right() {
        R++;
        ADD(R);
    }

    void add_left() {
        L--;
        ADD(L);
    }

    void rem_right() {
        REM(R);
        R--;
    }

    void rem_left() {
        REM(L);
        L++;
    }

    auto get_ans() {
        return z;
    }

    // --- STATE --- //





    Mo(vector<pair<int, int>> Q_, vector<int> a_) : a(a_) {
        BLOCK_SIZE = (int)sqrt((int)a.size()) + 1;

        for (int i = 0; i < (int)Q_.size(); i++) {
            Q.push_back({ Q_[i].first, Q_[i].second, i });
        }
        sort(Q.begin(), Q.end());

        ans.resize((int)Q.size());
        L = 0; R = -1;
    }

    void GO() {
        for (int i = 0; i < (int)ans.size(); i++) {
            while (R < Q[i].r) {
                add_right();
            }

            while (L > Q[i].l) {
                add_left();
            }

            while (R > Q[i].r) {
                rem_right();
            }

            while (L < Q[i].l) {
                rem_left();
            }

            ans[Q[i].id] = get_ans();
        }
    }

    void print_ans() {
        for (auto p : ans) {
            cout << p << '\n';
        }
    }

private:
    vector<int> ans;

    vector<QUERY> Q;
    vector<int> a;

    int L, R;
};

void Solve(int n, vector<int> a, int q, vector<pair<int, int>> Q) {
    for (int i = 0; i < q; i++) {
        --Q[i].first;
        --Q[i].second;
    }
    Mo W(Q, a); W.GO();
    W.print_ans();
}
