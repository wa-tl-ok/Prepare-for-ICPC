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

int bs_ll(vector<int>& arr, int target) {
    if (arr[0] >= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] >= target) {
            right = mid - 1;
        }
        else {
            if (arr[mid + 1] >= target) {
                return mid;
            }
            left = mid + 1;
        }
    }
    return left;
}

int bs_rr(vector<int>& arr, int target) {
    if (arr[arr.size() - 1] <= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

void Solve() {
    int H, W; cin >> H >> W;
    int cx, cy; cin >> cx >> cy;

    map<int, vector<int>> X; map<int, bool> VX;
    map<int, vector<int>> Y; map<int, bool> VY;

    int N; cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        
        X[x].push_back(y); VX[x] = true;
        Y[y].push_back(x); VY[y] = true;
    }

    for (auto& P : X) {
        sort(P.second.begin(), P.second.end());
    }

    for (auto& P : Y) {
        sort(P.second.begin(), P.second.end());
    }

    int Q; cin >> Q;

    for (int i = 0; i < Q; i++) {
        char q; cin >> q;
        int l; cin >> l;

        if (q == 'U') {
            if (VY[cy] == false) {
                cx -= l; cx = max(1LL, cx);
            }
            else {
                if (bs_ll(Y[cy], cx) == -1) {
                    cx -= l; cx = max(1LL, cx);
                }
                else {
                    int f = Y[cy][bs_ll(Y[cy], cx)] + 1;
                    cx -= l; cx = max(1LL, cx);
                    cx = max(cx, f);
                }
            }
        }
        else if (q == 'D') {
            if (VY[cy] == false) {
                cx += l; cx = min(H, cx);
            }
            else {
                if (bs_rr(Y[cy], cx) == -1) {
                    cx += l; cx = min(H, cx);
                }
                else {
                    int f = Y[cy][bs_rr(Y[cy], cx)] - 1;
                    cx += l; cx = min(H, cx);
                    cx = min(cx, f);
                }
            }
        }
        else if (q == 'R') {
            if (VX[cx] == false) {
                cy += l; cy = min(W, cy);
            }
            else {
                if (bs_rr(X[cx], cy) == -1) {
                    cy += l; cy = min(W, cy);
                }
                else {
                    int f = X[cx][bs_rr(X[cx], cy)] - 1;
                    cy += l; cy = min(W, cy);
                    cy = min(cy, f);
                }
            }
        }
        else {
            if (VX[cx] == false) {
                cy -= l; cy = max(1LL, cy);
            }
            else {
                if (bs_ll(X[cx], cy) == -1) {
                    cy -= l; cy = max(1LL, cy);
                }
                else {
                    int f = X[cx][bs_ll(X[cx], cy)] + 1;
                    cy -= l; cy = max(1LL, cy);
                    cy = max(cy, f);
                }
            }
        }

        cout << cx << ' ' << cy << '\n';
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
