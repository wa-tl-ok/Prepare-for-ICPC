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

namespace MATH {
    int randomabint(int a, int b) {
        return a + rand() % (b - a + 1);
    }

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b; b = a % b; a = temp;
        }
        return a;
    }

    int gcd_array(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) {
            return 0;
        }
        int result = arr[0];
        FOR(i, 1, n - 1) {
            result = gcd(result, arr[i]);
            if (result == 1) {
                break;
            }
        }
        return result;
    }

    int lcm(int a, int b) {
        if ((int)(a) * (b / gcd(a, b)) > 2e18) {
            return (int)2e18;
        }
        else {
            return (a) * (b / gcd(a, b));
        }
    }

    int lcm_array(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) {
            return 0;
        }
        double result = arr[0];
        for (int i = 1; i < n; ++i) {
            result = lcm((int)result, arr[i]);
            if (result >= 2e18) {
                return (int)2e18;
            }
        }
        return (int)result;
    }

    int fast_power_mod(int a, int n, int mod) {
        if (n == 0) {
            return 1;
        }
        int result = 1;
        int base = a;
        while (n > 0) {
            if (n % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            n = n / 2;
        }
        return result % mod;
    }

    int fast_power(int a, int n) {
        if (n == 0) {
            return 1;
        }
        int result = 1;
        int base = a;
        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n = n / 2;
        }
        return result;
    }

    int safe_pow(int a, int b) {
        int p = 1;
        for (int i = 0; i < b; i++) {
            double q = p;
            q *= a;
            if (q > 2e18) {
                return 2e18;
            }
            p *= a;
        }
        return p;
    }

    bool check_for_prime(int n) {
        assert(n > 0);
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    bool mr_check_for_prime(int n) {
        assert(n > 0);
        if (n == 1) {
            return false;
        }
        if (n == 2 || n == 3) {
            return true;
        }
        for (int test = 0; test < 5; ++test) {
            int a = randomabint(2, n - 2);
            int s = 0;
            int d = n - 1;
            while (d % 2 == 0) {
                s += 1;
                d /= 2;
            }
            int x = fast_power_mod(a, d, n);
            if (x != 1 && x != n - 1) {
                int F = 0;
                for (int i = 0; i < s - 1; ++i) {
                    x = (x * x) % n;
                    if (x == n - 1) {
                        F = 1;
                        break;
                    }
                }
                if (F == 0) {
                    return false;
                }
            }
        }
        return true;
    }

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
}

void Solve() {
    int n, k, q; cin >> n >> k >> q;

    vector<vector<int>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(k);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> M[i][j];
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < k; j++) {
            M[i][j] = M[i][j] | M[i - 1][j];
        }
    }

    vector<vector<int>> A(k);
    for (int i = 0; i < k; i++) {
        A[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            A[j][i] = M[i][j];
        }
    }

    for (int qq = 0; qq < q; qq++) {
        int m; cin >> m;

        int ans = -1;
        bool F = true;

        int L = 0;
        int R = n - 1;

        for (int i = 0; i < m; i++) {
            int row; cin >> row;
            char O; cin >> O; 
            int val; cin >> val;

            if (O == '>') {
                if (val >= A[row - 1][n - 1]) {
                    ans = -1;
                    F = false;
                }
                else {
                    L = max(L, MATH::bs_rr(A[row - 1], val));
                }
            }
            else {
                if (val <= A[row - 1][0]) {
                    ans = -1;
                    F = false;
                }
                else {
                    R = min(R, MATH::bs_ll(A[row - 1], val));
                }
            }
        }

        if (F == false) {
            cout << -1 << '\n';
        }
        else {
            if (L > R) {
                cout << -1 << '\n';
            }
            else {
                cout << L + 1 << '\n';
            }
        }
    }
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

    // auto end = chrono::high_resolution_clock::now();

    /*
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;
    */

    return 0;
}
