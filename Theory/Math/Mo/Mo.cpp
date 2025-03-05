const int BLOCK_SIZE = 1000;

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

    void ADD(int G) {

    }

    void REM(int G) {

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
        return 0;
    }

        // --- STATE --- //





    Mo(vector<pair<int, int>> Q_, vector<int> a_) : a(a_) {
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
            cout << p << ' ';
        }
    }

private:
    vector<int> ans;

    vector<QUERY> Q;
    vector<int> a;

    int L, R;
};
