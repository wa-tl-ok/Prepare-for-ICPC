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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int H, W; cin >> H >> W;

    vector<vector<char>> A(H);
    for (int i = 0; i < H; i++) {
        A[i].resize(W);
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<char>> B(H);
    for (int i = 0; i < H; i++) {
        B[i].resize(W);
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> B[i][j];
        }
    }

    for (int s = 0; s < H; s++) {
        for (int t = 0; t < W; t++) {
            bool f = true;

            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (A[(i - s + H) % H][(j - t + W) % W] != B[i][j]) {
                        f = false;
                    }
                }
            }

            if (f == true) {
                cout << "Yes";
                return 0;
            }
        }
    }

    cout << "No";

    return 0;
}
