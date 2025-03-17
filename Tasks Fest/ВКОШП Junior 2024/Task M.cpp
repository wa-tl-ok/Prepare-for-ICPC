#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>

using namespace std;

#define int long long

class Treap {
public:
    struct Node {
        int X;
        int Y;

        int cnt;

        int K;
        int S;
        int ID;

        Node* l;
        Node* r;

        Node(int k, int s, int id) :
            X(k), Y(rand()),
            cnt(1),
            K(k), S(s), ID(id),
            l(nullptr), r(nullptr) {}
    };

    Treap() : root(nullptr), size(0) {
        srand(static_cast<unsigned>(time(0)));
    }

    void Add(int pos, vector<int> v) {
        if (pos == -1) {
            pos = size;
        }

        Node* new_node = new Node(v[0], v[1], v[2]);

        Node* A;
        Node* B;

        split(root, A, B, pos);

        root = merge(merge(A, new_node), B);

        size++;
    }

    void Del(int pos) {
        ++pos;

        Node* A, * B, * M;

        split(root, A, B, pos);
        split(A, A, M, pos - 1);

        delete M;

        root = merge(A, B);
        --size;
    }

    array<int, 3> Max(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int MXK;
        if (M) {
            MXK = M->K;
        }
        else {
            MXK = -1;
        }

        int S_ = M->S;
        int ID_ = M->ID;

        root = merge(merge(A, M), B);

        return { MXK, S_, ID_ };
    }

    array<int, 3> Get(int pos) {
        return Max(pos, pos);
    }

    int Size() {
        return size;
    }

private:
    Node* root;
    int size;

    int min(int a, int b) {
        if (a < b) {
            return a;
        }
        return b;
    }

    int max(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    void updateNode(Node* v) {
        if (v) {
            v->cnt = (v->l ? v->l->cnt : 0) + (v->r ? v->r->cnt : 0) + 1;
            v->K = max(v->X, max(v->l ? v->l->K : -1, v->r ? v->r->K : -1));
        }
    }

    void split(Node* v, Node*& A, Node*& B, int x, int now = 0) {
        if (!v) {
            A = nullptr;
            B = nullptr;
            return;
        }

        int cur = now + 1;
        if (v->l) {
            cur += v->l->cnt;
        }

        if (x < cur) {
            split(v->l, A, v->l, x, now);
            B = v;
        }
        else {
            int offset = now + 1;
            if (v->l) {
                offset += v->l->cnt;
            }

            split(v->r, v->r, B, x, offset);
            A = v;
        }

        updateNode(v);
    }

    Node* merge(Node* A, Node* B) {
        if (!A) {
            return B;
        }
        if (!B) {
            return A;
        }

        if (A->Y > B->Y) {
            A->r = merge(A->r, B);

            updateNode(A);

            return A;
        }
        else {
            B->l = merge(A, B->l);

            updateNode(B);

            return B;
        }
    }
};

void Solve() {
    int n, x, D;
    cin >> n;
    cin >> x;
    cin >> D;

    Treap T;
    for (int i = 0; i < n; i++) {
        int k, s; cin >> k >> s;
        T.Add(-1, { k, s, i });
    }

    vector<vector<array<int, 3>>> Time_line(D + 1);
    unordered_set<int> ALL;

    for (int time = 0; time <= D; time++) {
        if (ALL.size() == n) {
            cout << time << '\n';
            return;
        }

        if (Time_line[time].size() > 0) {
            sort(Time_line[time].begin(), Time_line[time].end());

            for (auto& v : Time_line[time]) {
                int s = v[0];
                int k = v[1];
                int id = v[2];

                int l = -1;
                int r = T.Size();

                while (l + 1 != r) {
                    int m = (l + r) >> 1;

                    if (T.Max(m, T.Size() - 1)[0] >= k) {
                        l = m;
                    }
                    else {
                        r = m;
                    }
                }

                T.Add(r, { k, s, id });
            }
        }

        auto k_s_id = T.Get(0);

        int k_first = k_s_id[0];
        int s_first = k_s_id[1];
        int id_first = k_s_id[2];

        T.Del(0);

        ALL.insert(id_first);

        if (time + 1 + x * s_first <= D) {
            Time_line[time + 1 + x * s_first].push_back({ s_first, k_first, id_first });
        }
    }

    cout << -1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
