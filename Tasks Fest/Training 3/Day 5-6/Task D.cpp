// #define _CRT_SECURE_NO_WARNINGS 

#include <iostream> 
#include <algorithm> 
#include <cmath> 
#include <climits> 
#include <vector> 
#include <queue> 
#include <deque> 
#include <array> 
#include <list> 
#include <stack> 
#include <tuple> 
#include <set> 
#include <unordered_set> 
#include <map> 
#include <unordered_map> 
#include <string> 
#include <cstring> 
#include <random> 
#include <bitset> 
#include <iomanip> 
#include <iterator> 
#include <functional> 
#include <ctime> 
#include <chrono> 
#include <cctype> 
#include <fstream> 
#include <ranges> 
#include <numeric> 
#include <complex> 
#include <cassert> 

using namespace std;

// #pragma GCC optimize("Ofast") 
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int               long long 
#define sz(x)             ((int)(x).size()) 
#define mp                make_pair 
#define all(x)            (x).begin(), (x).end() 
#define pb                push_back 
#define pf                push_front 
#define ff                first 
#define ss                second 
#define unique(x)         (x).erase(unique(all(x)), (x).end()) 
#define min3(a, b, c)     min(a, min(b, c)) 
#define max3(a, b, c)     max(a, max(b, c)) 
#define FOR(i, a, b)      for (int i = (a); i <= (b); i++) 
#define ROF(i, a, b)      for (int i = (a); i >= (b); i--) 

using vi = vector<int>;
using vd = vector<double>;
using vpii = vector<pair<int, int>>;
using vpdd = vector<pair<double, double>>;
using pii = pair<int, int>;
using pdd = pair<double, double>;

template <typename Container>
void PRINT(const Container& container) {
    for (const auto& e : container) {
        cout << e << ' ';
    } cout << '\n';
}

void print_double(double ans, int num) {
    cout << fixed << setprecision(num) << ans << '\n';
}

const int inf = 1e18;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int bs_ll(vector<int>& arr, int target) {
    /*
        Find max index of number in arr that < target
    */
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

int bs_rl(vector<int>& arr, int target) {
    /*
        Find min index of number that >= target
    */
    if (arr[arr.size() - 1] < target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

int bs_lr(vector<int>& arr, int target) {
    /*
        Find max index of number that <= target
    */
    if (arr[0] > target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return right;
}

int bs_rr(vector<int>& arr, int target) {
    /*
        Find min index of number that > target
    */
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
    int a, b; cin >> a >> b;
    int n, m; cin >> n >> m;

    map<int, vector<int>> MAP_X;
    map<int, vector<int>> MAP_Y;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;

        MAP_X[x].push_back(y);
        MAP_Y[y].push_back(x);
    }

    for (auto& [x, vec_y] : MAP_X) {
        sort(vec_y.begin(), vec_y.end());
    }

    for (auto& [y, vec_x] : MAP_Y) {
        sort(vec_x.begin(), vec_x.end());
    }

    int Alice = 0;
    int Bob = 0;

    int F = true;

    int U = 1;
    int D = a;
    int L = 1;
    int R = b;

    for (int i = 0; i < m; i++) {
        char c; int k; cin >> c >> k;

        if (c == 'U') {
            int predU = U + k - 1;

            for (auto it = MAP_X.begin(); it != MAP_X.end(); ++it) {
                auto& [x, vec_y] = *it;

                if (x <= predU) {
                    if (F == true) Alice += (bs_lr(vec_y, R) + 1) - (bs_ll(vec_y, L) + 1);
                    else Bob += (bs_lr(vec_y, R) + 1) - (bs_ll(vec_y, L) + 1);
                }
                else {
                    break;
                }
            }

            while (MAP_X.size() > 0 && (*MAP_X.begin()).first <= predU) {
                MAP_X.erase(MAP_X.begin());
            }

            U = predU + 1;
        }
        else if (c == 'D') {
            int predD = D - k + 1;

            for (auto it = MAP_X.rbegin(); it != MAP_X.rend(); ++it) {
                auto& [x, vec_y] = *it;

                if (x >= predD) {
                    if (F == true) Alice += (bs_lr(vec_y, R) + 1) - (bs_ll(vec_y, L) + 1);
                    else Bob += (bs_lr(vec_y, R) + 1) - (bs_ll(vec_y, L) + 1);
                }
                else {
                    break;
                }
            }

            while (MAP_X.size() > 0 && (*MAP_X.rbegin()).first >= predD) {
                MAP_X.erase(--MAP_X.end());
            }

            D = predD - 1;
        }
        else if (c == 'L') {
            int predL = L + k - 1;

            for (auto it = MAP_Y.begin(); it != MAP_Y.end(); ++it) {
                auto& [y, vec_x] = *it;

                if (y <= predL) {
                    if (F == true) Alice += (bs_lr(vec_x, D) + 1) - (bs_ll(vec_x, U) + 1);
                    else Bob += (bs_lr(vec_x, D) + 1) - (bs_ll(vec_x, U) + 1);
                }
                else {
                    break;
                }
            }

            while (MAP_Y.size() > 0 && (*MAP_Y.begin()).first <= predL) {
                MAP_Y.erase(MAP_Y.begin());
            }

            L = predL + 1;
        }
        else {
            int predR = R - k + 1;

            for (auto it = MAP_Y.rbegin(); it != MAP_Y.rend(); ++it) {
                auto& [y, vec_x] = *it;

                if (y >= predR) {
                    if (F == true) Alice += (bs_lr(vec_x, D) + 1) - (bs_ll(vec_x, U) + 1);
                    else Bob += (bs_lr(vec_x, D) + 1) - (bs_ll(vec_x, U) + 1);
                }
                else {
                    break;
                }
            }

            while (MAP_Y.size() > 0 && (*MAP_Y.rbegin()).first >= predR) {
                MAP_Y.erase(--MAP_Y.end());
            }

            R = predR - 1;
        }

        if (F == true) {
            F = false;
        }
        else {
            F = true;
        }
    }

    cout << Alice << ' ' << Bob << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    /*
                      ________________
                     / Just solved it \
                     |   in my mind   |
                     \________________/
                    /
                   /
　　　　　／＞　 フ         ___________
　　　　　| 　_　 _|       |          |
　 　　　／`ミ _x 彡       |   WA 2   |
　　 　 /　　　 　 |       |__________|
　　　 /　 ヽ　　 ﾉ        /          /
　／￣|　　 |　|　|       /_________ /
　| (￣ヽ＿_ヽ_)_)
　＼二つ

    */

    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    // auto start = chrono::high_resolution_clock::now();

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

    // auto end = chrono::high_resolution_clock::now();

    /*
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;
    */

    return 0;
}
