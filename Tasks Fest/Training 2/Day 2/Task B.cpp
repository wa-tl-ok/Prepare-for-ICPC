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
#include <iomanip>

using namespace std;

class FenwickTree2D {
public:
    FenwickTree2D(int rows, int cols) : rows(rows), cols(cols) {
        field.assign(rows + 1, vector<int>(cols + 1, 0));
    }

    void plus(int x, int y, int value) {
        for (int i = x + 1; i <= rows; i += i & -i) {
            for (int j = y + 1; j <= cols; j += j & -j) {
                field[i][j] += value;
            }
        }
    }

    void change(int x, int y, int value) {
        int current = range_query(x, y, x, y);
        plus(x, y, value - current);
    }

    int query(int x, int y) const {
        int sum = 0;
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                sum += field[i][j];
            }
        }
        return sum;
    }

    int range_query(int x1, int y1, int x2, int y2) const {
        return query(x2, y2)
            - (x1 > 0 ? query(x1 - 1, y2) : 0)
            - (y1 > 0 ? query(x2, y1 - 1) : 0)
            + (x1 > 0 && y1 > 0 ? query(x1 - 1, y1 - 1) : 0);
    }

private:
    vector<vector<int>> field;
    int rows, cols;
};

void Solve() {
    int n, m; cin >> n >> m;
    vector<vector<char>> C(n);
    for (int i = 0; i < n; i++) {
        C[i].resize(m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> C[i][j];
        }
    }

    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        V[i].resize(m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            V[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        if (C[0][i] == '.') {
            V[0][i] = 1;
        }
        else {
            V[0][i] = 0;
        }
    }
    for (int j = 0; j < n; j++) {
        if (C[j][0] == '.') {
            V[j][0] = 1;
        }
        else {
            V[j][0] = 0;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (C[i][j] == '.') {
                if (V[i - 1][j] == 1 || V[i][j - 1] == 1) {
                    V[i][j] = 1;
                }
            }
        }
    }

    vector<vector<int>> Bad(n);
    for (int i = 0; i < n; i++) {
        Bad[i].resize(m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Bad[i][j] = 0;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (C[i - 1][j] == 'X' && C[i][j - 1] == 'X') {
                Bad[i][j] = 1;
            }
        }
    }

    FenwickTree2D FT(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            FT.plus(i, j, Bad[i][j]);
        }
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        if (l == r || FT.range_query(0, l, n - 1, r - 1) == 0) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

int main() {
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
