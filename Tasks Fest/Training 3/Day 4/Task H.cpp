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

int mod = 1e9 + 7;

class Matrix {
public:
    Matrix(const vector<vector<int>>& matrix) : data(matrix) {}

    vector<vector<int>> getData() const {
        return data;
    }

    Matrix rotateclockwise() const {
        vector<vector<int>> rotated_matrix(data[0].size(), vector<int>(data.size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                rotated_matrix[j][data.size() - 1 - i] = data[i][j];
            }
        }
        return Matrix(rotated_matrix);
    }

    Matrix operator+(const Matrix& other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
            throw invalid_argument("Matrices dimensions do not match for addition.");
        }

        vector<vector<int>> result_matrix(data.size(), vector<int>(data[0].size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result_matrix[i][j] = (data[i][j] + other.data[i][j] + mod) % mod;
            }
        }

        return Matrix(result_matrix);
    }

    Matrix operator-(const Matrix& other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
            throw invalid_argument("Matrices dimensions do not match for subtraction.");
        }

        vector<vector<int>> result_matrix(data.size(), vector<int>(data[0].size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result_matrix[i][j] = (data[i][j] - other.data[i][j] + mod) % mod;
            }
        }

        return Matrix(result_matrix);
    }

    Matrix operator*(const Matrix& other) const {
        size_t rows1 = data.size();
        size_t columns1 = data[0].size();
        size_t rows2 = other.data.size();
        size_t columns2 = other.data[0].size();

        if (columns1 != rows2) {
            throw invalid_argument("Matrices dimensions do not match for multiplication.");
        }

        vector<vector<int>> result_matrix(rows1, vector<int>(columns2, 0));
        for (size_t i = 0; i < rows1; ++i) {
            for (size_t j = 0; j < columns2; ++j) {
                for (size_t k = 0; k < columns1; ++k) {
                    result_matrix[i][j] += data[i][k] * other.data[k][j];
                    result_matrix[i][j] %= mod;
                }
            }
        }

        return Matrix(result_matrix);
    }

    bool operator==(const Matrix& other) const {
        return data == other.data;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix pow(int n) const {
        if (data.size() != data[0].size()) {
            throw invalid_argument("Matrix must be square for exponentiation.");
        }

        Matrix result = identity(data.size());
        Matrix base = *this;

        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n /= 2;
        }

        return result;
    }

    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

private:
    vector<vector<int>> data;

    static Matrix identity(size_t size) {
        vector<vector<int>> identity_matrix(size, vector<int>(size, 0));
        for (size_t i = 0; i < size; ++i) {
            identity_matrix[i][i] = 1;
        }
        return Matrix(identity_matrix);
    }
};

void Solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        g[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = a[i] ^ a[j];

            int cnt = 0;
            for (int k = 0; k < 64; k++) {
                if (x & (1LL << k)) {
                    ++cnt;
                }
            }

            if (cnt % 3 == 0) {
                g[i][j] = 1;
            }
            else {
                g[i][j] = 0;
            }
        }
    }

    Matrix G(g);

    vector<vector<int>> G_K = G.pow(k - 1).getData();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = (ans + G_K[i][j]) % mod;
        }
    }
    cout << ans;
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
