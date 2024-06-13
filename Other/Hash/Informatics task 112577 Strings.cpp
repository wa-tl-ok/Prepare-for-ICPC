//https://informatics.msk.ru/mod/statements/view.php?id=33342&chapterid=112577#1

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
#include <random>

using namespace std;

using ll = long long;
using str = string;

ll mod = 1e9 + 7;
str S, T;
vector<ll> Step(300005);
vector<ll> Pref_Hash_S;

ll Take_Hash(int l, int r, vector<ll>& Pref) {
    if (l == 0) {
        return (((Pref[r] + mod) % mod) * Step[(int)S.size() - l]) % mod;
    }
    return (((Pref[r] - Pref[l - 1] + mod) % mod) * Step[(int)S.size() - l]) % mod;
}

int main() {
    cin >> S >> T;
    int PS = (int)S.size();
    S = S + S + T;

    Step[0] = 1;
    for (int i = 1; i < 300005; ++i) {
        Step[i] = (Step[i - 1] * 61) % mod;
    }

    Pref_Hash_S.resize((int)S.size());
    if (Pref_Hash_S[0] >= 'A' && Pref_Hash_S[0] <= 'Z') {
        Pref_Hash_S[0] = S[0] - 'A' + 27;
    }
    else {
        Pref_Hash_S[0] = S[0] - 'a' + 1;
    }

    for (int i = 1; i < (int)S.size(); ++i) {
        if (Pref_Hash_S[i] >= 'A' && Pref_Hash_S[i] <= 'Z') {
            Pref_Hash_S[i] = (Pref_Hash_S[i - 1] + ((S[i] - 'A' + 27) * Step[i]) % mod) % mod;
        }
        else {
            Pref_Hash_S[i] = (Pref_Hash_S[i - 1] + ((S[i] - 'a' + 1) * Step[i]) % mod) % mod;
        }
    }

    int l, r;
    int tl = PS * 2;
    int tr = PS * 3 - 1;

    for (l = 0; l < (int)S.size(); l++) {
        r = l + PS - 1;
        if (r == 2 * PS) {
            break;
        }
        if (Take_Hash(l, r, Pref_Hash_S) == Take_Hash(tl, tr, Pref_Hash_S)) {
            cout << (PS - l) % PS;
            return 0;
        }
    }
    cout << -1;
    return 0;
}
