int BLOCK_SIZE = 1000;

struct Trio {
    int First;
    int Second;
    int Third; // 1 -> Query ---> First == l; Second == r;
               // 2 -> Update ---> First = ind; Second == new_elem;
};

class Mo3D {
public:
    struct QUERY {
        int l, r, t, id;

        bool operator<(const QUERY& other) const {
            int block1_l = l / BLOCK_SIZE;
            int block2_l = other.l / BLOCK_SIZE;

            if (block1_l != block2_l) {
                return block1_l < block2_l;
            }

            int block1_r = r / BLOCK_SIZE;
            int block2_r = other.r / BLOCK_SIZE;

            if (block1_r != block2_r) {
                return block1_r < block2_r;
            }

            return t > other.t;
        }
    };





    // --- STATE --- //

    int z = 0;

    void ADD(int G) {
        z += a[G];
    }

    void REM(int G) {
        z -= a[G];
    }

    void ADD_TIME() {
        auto pos_newval = changes[T];

        int pos = pos_newval.first;
        int newval = pos_newval.second;

        if (pos >= L && pos <= R) {
            z -= a[pos];
            z += newval;
        }

        a[pos] = newval;
    }

    void REM_TIME() {
        auto pos_oldval = unchanges[T];

        int pos = pos_oldval.first;
        int oldval = pos_oldval.second;

        if (pos >= L && pos <= R) {
            z -= a[pos];
            z += oldval;
        }

        a[pos] = oldval;
    }

    void add_time() {
        T++;
        ADD_TIME();
    }

    void rem_time() {
        REM_TIME();
        T--;
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





    Mo3D(vector<Trio> Q_, vector<int> a_) : a(a_), ended_a(a_) {
        BLOCK_SIZE = (int)cbrtl(pow((int)a.size(), 2)) + 1;

        int t = -1; int j = 0;
        for (int i = 0; i < (int)Q_.size(); i++) {
            if (Q_[i].Third == 1) {
                Q.push_back({ Q_[i].First, Q_[i].Second, t, j });
                ++j;
            }
            else {
                ++t;
                changes.push_back({ Q_[i].First, Q_[i].Second });
                unchanges.push_back({ Q_[i].First, ended_a[Q_[i].First] });
                ended_a[Q_[i].First] = Q_[i].Second;
            }
        }
        sort(Q.begin(), Q.end());

        ans.resize((int)Q.size());
        L = 0; R = -1, T = -1;
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

            while (T < Q[i].t) {
                add_time();
            }

            while (T > Q[i].t) {
                rem_time();
            }

            ans[Q[i].id] = get_ans();
        }
    }

    void print_ans() {
        for (auto p : ans) {
            cout << p << ' ';
        }
    }

private:
    vector<int> ans;

    vector<QUERY> Q;
    vector<int> a, ended_a;

    vector<pair<int, int>> changes;
    vector<pair<int, int>> unchanges;

    int L, R, T;
};
