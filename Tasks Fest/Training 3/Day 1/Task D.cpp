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

/*
Add(int pos, int x) - Добавить элемент x на позицию pos (если pos = 0, то добавить элемент в начало)
Del(int pos) - Удалить элемент на поиции pos

Rev(int l, int r) - Перевернуть отрезок [l r]
Swap(int l1, int r1, int l2, int r2) - Поменять местами отрезки [l1 r1] и [l2 r2]

Shift_To_Right(int l, int r) - Сдвинуть отрезок [l r] в конец
Shift_To_Left(int l, int r) - Сдвинуть отрезок [l r] в начало
Shift_Right(int l, int r) - Циклически сдвинуть отрезок [l r] вправо на 1
Shift_Left(int l, int r) - Циклически сдвинуть отрезок [l r] влево на 1
K_Shift_Right(int l, int r, int k) - Циклически сдвинуть отрезок [l r] вправо на k
K_Shift_Left(int l, int r, int k) - Циклически сдвинуть отрезок [l r] влево на k

Sum(int l, int r) - Найти сумму на отрезке [l r]
Min(int l, int r) - Найти минимум на отрезке [l r]
Max(int l, int r) - Найти максимум на отрезке [l r]
Get(int pos) - Найти элемент на позиции pos

Set(int p, int new_val) - Обновить значение на позиции p
Plus(int p, int x) - Добавить x к элементу на позиции p

RangeSet(int l, int r, int x) - Обновить значение всех элементов на отрезке [l, r]
RangePlus(int l, int r, int x) - Добавить x ко всем элементам на отрезке [l, r]
RangeDel(int l, int r) - Удалить все элементы с l по r

Clear() - Очистить трипу
Print() - Вывеести трипу
Size() - Найти размер трипы
*/

class Treap {
public:
    struct Node {
        int X;
        int Y;

        int cnt;

        int sum;
        int minVal;
        int maxVal;

        bool rev;

        int add_lazy;
        int set_lazy;
        bool has_set_lazy;

        bool shift;
        int shift_amount;

        Node* l;
        Node* r;

        Node(int v) :
            X(v), Y(rand()),
            cnt(1),
            sum(v), minVal(v), maxVal(v),
            rev(false),
            add_lazy(0), set_lazy(0), has_set_lazy(0),
            shift(false), shift_amount(0),
            l(nullptr), r(nullptr) {}
    };

    Treap() : root(nullptr), size(0) {
        srand(static_cast<unsigned>(time(0)));
    }

    Treap(const vector<int>& values) : root(nullptr), size(0) {
        srand(static_cast<unsigned>(time(0)));
        for (const int& val : values) {
            Add(-1, val);
        }
    }

    ~Treap() {
        Clear();
    }

    void Add(int pos, int x) {
        if (pos == -1) {
            pos = size;
        }

        Node* new_node = new Node(x);

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

    void Rev(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        if (M) {
            M->rev ^= 1;
        }

        root = merge(merge(A, M), B);
    }

    void Swap(int l1, int r1, int l2, int r2) {
        ++l1;
        ++r1;
        ++l2;
        ++r2;

        Node* A, * B, * C, * D, * E;

        split(root, A, E, r2);
        split(A, A, D, l2 - 1);
        split(A, A, C, r1);
        split(A, A, B, l1 - 1);

        root = merge(merge(merge(merge(A, D), C), B), E);
    }

    void Shift_To_Right(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        root = merge(merge(A, B), M);
    }

    void Shift_To_Left(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        root = merge(merge(M, A), B);
    }

    void Shift_Right(int l, int r) {
        int x = Get(r);
        Del(r);
        Add(l, x);
    }

    void Shift_Left(int l, int r) {
        int x = Get(l);
        Del(l);
        Add(r, x);
    }

    void K_Shift_Right(int l, int r, int k) {
        k %= (r - l + 1);

        if (k != 0) {
            --k;

            int l1 = l;
            int r1 = r - k - 1;
            int l2 = r - k;
            int r2 = r;

            Swap(l1, r1, l2, r2);
        }
    }

    void K_Shift_Left(int l, int r, int k) {
        k %= (r - l + 1);

        if (k != 0) {
            --k;

            int l1 = l;
            int r1 = l + k;
            int l2 = l + k + 1;
            int r2 = r;

            Swap(l1, r1, l2, r2);
        }
    }

    int Sum(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int result;
        if (M) {
            result = M->sum;
        }
        else {
            result = 0;
        }

        root = merge(merge(A, M), B);

        return result;
    }

    int Min(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int result;
        if (M) {
            result = M->minVal;
        }
        else {
            result = 2e9;
        }

        root = merge(merge(A, M), B);

        return result;
    }

    int Max(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        int result;
        if (M) {
            result = M->maxVal;
        }
        else {
            result = -2e9;
        }

        root = merge(merge(A, M), B);

        return result;
    }

    int Get(int pos) {
        return Sum(pos, pos);
    }

    void Set(int p, int new_val) {
        ++p;

        Node* A, * B, * M;

        split(root, A, B, p);
        split(A, A, M, p - 1);

        if (M) {
            M->X = new_val;
            M->sum = new_val;
            M->minVal = new_val;
            M->maxVal = new_val;
        }

        root = merge(merge(A, M), B);
    }

    void Plus(int p, int x) {
        ++p;

        Node* A, * B, * M;

        split(root, A, B, p);
        split(A, A, M, p - 1);

        if (M) {
            M->X += x;
            M->sum += x;
            M->minVal += x;
            M->maxVal += x;

            updateNode(M);
        }

        root = merge(merge(A, M), B);
    }

    void RangeSet(int l, int r, int x) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        if (M) {
            applySetLazy(M, x);
        }

        root = merge(merge(A, M), B);
    }

    void RangePlus(int l, int r, int x) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        if (M) {
            applyAddLazy(M, x);
        }

        root = merge(merge(A, M), B);
    }

    void RangeDel(int l, int r) {
        ++l;
        ++r;

        Node* A, * B, * M;

        split(root, A, B, r);
        split(A, A, M, l - 1);

        root = merge(A, B);

        size -= (r - l + 1);
    }

    void Clear() {
        clearTree(root);
        root = nullptr;
        size = 0;
    }

    void Print() {
        printTree(root);
        cout << endl;
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

    void push(Node* v) {
        if (!v) {
            return;
        }

        if (v->rev) {
            v->rev = false;

            swap(v->l, v->r);

            if (v->l) v->l->rev ^= true;
            if (v->r) v->r->rev ^= true;
        }

        if (v->has_set_lazy) {
            if (v->l) {
                applySetLazy(v->l, v->set_lazy);
            }

            if (v->r) {
                applySetLazy(v->r, v->set_lazy);
            }

            v->has_set_lazy = false;
        }
        else if (v->add_lazy) {
            if (v->l) {
                applyAddLazy(v->l, v->add_lazy);
            }

            if (v->r) {
                applyAddLazy(v->r, v->add_lazy);
            }

            v->add_lazy = 0;
        }

        if (v->shift) {
            if (v->l) {
                applyShift(v->l, v->shift_amount);
            }

            if (v->r) {
                applyShift(v->r, v->shift_amount);
            }

            v->shift = false;
            v->shift_amount = 0;
        }
    }

    void applyAddLazy(Node* v, int add) {
        if (!v) {
            return;
        }

        if (v->has_set_lazy) {
            v->set_lazy += add;
        }
        else {
            v->X += add;

            v->sum += add * v->cnt;
            v->minVal += add;
            v->maxVal += add;

            v->add_lazy += add;
        }
    }

    void applySetLazy(Node* v, int set_val) {
        if (!v) {
            return;
        }

        v->X = set_val;

        v->sum = set_val * v->cnt;
        v->minVal = set_val;
        v->maxVal = set_val;

        v->set_lazy = set_val;
        v->add_lazy = 0;

        v->has_set_lazy = true;
    }

    void applyShift(Node* v, int shift_amount) {
        if (!v) {
            return;
        }

        v->shift_amount = shift_amount;
        v->shift = true;
    }

    void updateNode(Node* v) {
        if (v) {
            v->cnt = (v->l ? v->l->cnt : 0) + (v->r ? v->r->cnt : 0) + 1;
            v->sum = (v->l ? v->l->sum : 0) + (v->r ? v->r->sum : 0) + v->X;
            v->minVal = min(v->X, min(v->l ? v->l->minVal : 2e9, v->r ? v->r->minVal : 2e9));
            v->maxVal = max(v->X, max(v->l ? v->l->maxVal : -2e9, v->r ? v->r->maxVal : -2e9));
        }
    }

    void split(Node* v, Node*& A, Node*& B, int x, int now = 0) {
        if (!v) {
            A = nullptr;
            B = nullptr;
            return;
        }

        push(v);

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

        push(A);
        push(B);

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

    void clearTree(Node* A) {
        if (!A) {
            return;
        }

        clearTree(A->l);
        clearTree(A->r);

        delete A;
    }

    void printTree(Node* v) {
        if (!v) {
            return;
        }

        push(v);

        printTree(v->l);
        cout << v->X << " ";
        printTree(v->r);
    }
};

void Solve() {
    vector<int> ANS;

    int n; cin >> n;
    string s1; cin >> s1;
    string s2; cin >> s2;

    Treap a;
    for (int i = 0; i < n; i++) {
        if (s1[i] == '0') {
            a.Add(-1, 0);
        }
        else {
            a.Add(-1, 1);
        }
    }

    Treap b;
    for (int i = 0; i < n; i++) {
        if (s2[i] == '0') {
            b.Add(-1, 0);
        }
        else {
            b.Add(-1, 1);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (a.Sum(i, i) % 2 == 0 && b.Sum(i, i) % 2 == 1) {
            if (a.Sum(0, 0) % 2 == 0) {
                // a : 0 ... 0
                // b : ..... 1

                a.RangePlus(0, i, 1);
                a.Rev(0, i);

                ANS.push_back(i + 1);
            }
            else {
                // a : 1 ... 0
                // b : ..... 1

                a.RangePlus(0, 0, 1);
                a.Rev(0, 0);

                ANS.push_back(0 + 1);

                a.RangePlus(0, i, 1);
                a.Rev(0, i);

                ANS.push_back(i + 1);
            }
        }
        else if (a.Sum(i, i) % 2 == 1 && b.Sum(i, i) % 2 == 0) {
            if (a.Sum(0, 0) % 2 == 1) {
                // a : 1 ... 1
                // b : ..... 0

                a.RangePlus(0, i, 1);
                a.Rev(0, i);

                ANS.push_back(i + 1);
            }
            else {
                // a : 0 ... 1
                // b : ..... 0

                a.RangePlus(0, 0, 1);
                a.Rev(0, 0);

                ANS.push_back(0 + 1);

                a.RangePlus(0, i, 1);
                a.Rev(0, i);

                ANS.push_back(i + 1);
            }
        }
        else {
            // OK
        }
    }

    cout << ANS.size() << ' '; PRINT(ANS);
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
