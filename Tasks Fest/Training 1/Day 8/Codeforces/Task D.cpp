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

void print(int a, int b, int c) {
    cout << a << " " << b << " " << c << endl;
}

void Solve() {
	int n; cin >> n;

	vector<pair<int, int>> p[2];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			p[(i + j) % 2].push_back({ i, j });
		}
	}

	for (int i = 0; i < n * n; i++) {
		int a; cin >> a;

        if (a == 1) {
            if (p[0].size() > 0) {
                int x = p[0][p[0].size() - 1].first;
                int y = p[0][p[0].size() - 1].second;
                p[0].pop_back();
                print(2, x, y);
            }
            else {
                int x = p[1][p[1].size() - 1].first;
                int y = p[1][p[1].size() - 1].second;
                p[1].pop_back();
                print(3, x, y);
            }
        }
        else if (a == 2) {
            if (p[1].size() > 0) {
                int x = p[1][p[1].size() - 1].first;
                int y = p[1][p[1].size() - 1].second;
                p[1].pop_back();
                print(1, x, y);
            }
            else {
                int x = p[0][p[0].size() - 1].first;
                int y = p[0][p[0].size() - 1].second;
                p[0].pop_back();
                print(3, x, y);
            }
        }
        else {
            if (p[0].size() > 0) {
                int x = p[0][p[0].size() - 1].first;
                int y = p[0][p[0].size() - 1].second;
                p[0].pop_back();
                print(2, x, y);
            }
            else {
                int x = p[1][p[1].size() - 1].first;
                int y = p[1][p[1].size() - 1].second;
                p[1].pop_back();
                print(1, x, y);
            }
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
