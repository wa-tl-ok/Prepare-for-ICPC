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
#include <cassert>

using namespace std;

#define int long long

class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void change(int pos, int val) {
        root = updatePoint(root, 0, n - 1, pos, val);
    }

    int query(int const_l, int const_r) {
        return queryRange(root, 0, n - 1, const_l, const_r);
    }

private:
    struct Node {
        int sum;
        Node* left;
        Node* right;

        Node() : sum(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->sum = val;
            return node;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            node->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            node->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

        node->sum = 0;
        if (node->left) {
            node->sum = node->left->sum;
        }
        if (node->right) {
            node->sum += node->right->sum;
        }

        return node;
    }

    int queryRange(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return 0;
        }

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return node->sum;
        }

        int mid = l + (r - l) / 2;

        int leftSum = queryRange(node->left, l, mid, const_l, const_r);
        int rightSum = queryRange(node->right, mid + 1, r, const_l, const_r);

        return leftSum + rightSum;
    }
};

void Solve() {
    int H, W, N, h, w;
    cin >> H >> W >> N >> h >> w;
    vector<vector<int>> M(H);
    for (int i = 0; i < H; i++) {
        M[i].resize(W);
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> M[i][j];
        }
    }
    map<int, int> SUM;
    ImplicitSegmentTree st(305);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            SUM[M[i][j]] += 1;
            if (SUM[M[i][j]] == 1) {
                st.change(M[i][j], 1);
            }
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            SUM[M[i][j]] -= 1;
            if (SUM[M[i][j]] == 0) {
                st.change(M[i][j], 0);
            }
        }
    }
    int cur_x = 0;
    int cur_y = 0;
    for (int trash1 = 0; trash1 <= H - h; trash1++) {
        cout << st.query(0, 303) << ' ';
        for (int trash2 = 0; trash2 <= W - w - 1; trash2++) {
            int rollback_y = cur_y;
            for (int rollback_x = cur_x; rollback_x < cur_x + h; rollback_x++) {
                assert(rollback_x < H && rollback_y < W && rollback_x >= 0 && rollback_y >= 0);
                SUM[M[rollback_x][rollback_y]] += 1;
                if (SUM[M[rollback_x][rollback_y]] == 1) {
                    st.change(M[rollback_x][rollback_y], 1);
                }
            }
            int del_y = cur_y + w;
            for (int del_x = cur_x; del_x < cur_x + h; del_x++) {
                assert(del_x < H && del_y < W && del_x >= 0 && del_y >= 0);
                SUM[M[del_x][del_y]] -= 1;
                if (SUM[M[del_x][del_y]] == 0) {
                    st.change(M[del_x][del_y], 0);
                }
            }
            cur_y += 1;
            cout << st.query(0, 303) << ' ';
        }
        for (int trash2 = 0; trash2 <= W - w - 1; trash2++) {
            cur_y -= 1;
            int rollback_y = cur_y + w;
            for (int rollback_x = cur_x; rollback_x < cur_x + h; rollback_x++) {
                assert(rollback_x < H && rollback_y < W && rollback_x >= 0 && rollback_y >= 0);
                SUM[M[rollback_x][rollback_y]] += 1;
                if (SUM[M[rollback_x][rollback_y]] == 1) {
                    st.change(M[rollback_x][rollback_y], 1);
                }
            }
            int del_y = cur_y;
            for (int del_x = cur_x; del_x < cur_x + h; del_x++) {
                assert(del_x < H && del_y < W && del_x >= 0 && del_y >= 0);
                SUM[M[del_x][del_y]] -= 1;
                if (SUM[M[del_x][del_y]] == 0) {
                    st.change(M[del_x][del_y], 0);
                }
            }
        }
        if (cur_x + h < H) {
            for (int i = 0; i < w; i++) {
                SUM[M[cur_x][i]] += 1;
                if (SUM[M[cur_x][i]] == 1) {
                    st.change(M[cur_x][i], 1);
                }
            }
            for (int i = 0; i < w; i++) {
                SUM[M[cur_x + h][i]] -= 1;
                if (SUM[M[cur_x + h][i]] == 0) {
                    st.change(M[cur_x + h][i], 0);
                }
            }
            cur_x += 1;
            cout << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
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
