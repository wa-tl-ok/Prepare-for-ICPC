//https://informatics.msk.ru/mod/statements/view.php?id=33342&chapterid=1326#1

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

vector<ll> PHash(1000005);
vector<ll> RHash(1000005);
vector<ll> Step(1000005);
const ll mod = 1e9 + 7;
str S;
int n;

ll Take_PHash(int l, int r) {
    if (l == 0) {
        return (((PHash[r] + mod) % mod) * Step[n - l]) % mod;
    }
    return (((PHash[r] - PHash[l - 1] + mod) % mod) * Step[n - l]) % mod;
}

ll Take_RHash(int l, int r) {
    if (l == 0) {
        return (((RHash[r] + mod) % mod) * Step[n - l]) % mod;
    }
    return (((RHash[r] - RHash[l - 1] + mod) % mod) * Step[n - l]) % mod;
}

bool Check(int l, int r) {
    if (Take_PHash(l, r) == Take_RHash(n - r - 1, n - l - 1)) {
        return true;
    }
    return false;
}

void P() {
    PHash.resize((int)S.size());
    if (S[0] >= 'A' && S[0] <= 'Z') {
        PHash[0] = S[0] - 'A' + 27;
    }
    else {
        PHash[0] = S[0] - 'a' + 1;
    }
    for (int i = 1; i < (int)S.size(); ++i) {
        if (S[i] >= 'A' && S[i] <= 'Z') {
            PHash[i] = (PHash[i - 1] + ((S[i] - 'A' + 27) * Step[i]) % mod) % mod;
        }
        else {
            PHash[i] = (PHash[i - 1] + ((S[i] - 'a' + 1) * Step[i]) % mod) % mod;
        }
    }
}

void R() {
    reverse(S.begin(), S.end());
    RHash.resize((int)S.size());
    if (S[0] >= 'A' && S[0] <= 'Z') {
        RHash[0] = S[0] - 'A' + 27;
    }
    else {
        RHash[0] = S[0] - 'a' + 1;
    }
    for (int i = 1; i < (int)S.size(); ++i) {
        if (S[i] >= 'A' && S[i] <= 'Z') {
            RHash[i] = (RHash[i - 1] + ((S[i] - 'A' + 27) * Step[i]) % mod) % mod;
        }
        else {
            RHash[i] = (RHash[i - 1] + ((S[i] - 'a' + 1) * Step[i]) % mod) % mod;
        }
    }
}

void In() {
    cin >> S;
    n = (int)S.size();

    Step[0] = 1;
    for (int i = 1; i < 1000005; i++) {
        Step[i] = (Step[i - 1] * 61) % mod;
    }
}

int main() {
    In(); P(); R();
    for (int ind = 0; ind < (int)S.size(); ind++) {
        int l = 0;
        int r = min(ind, n - ind - 1) + 1;
        while (l + 1 != r) {
            int m = (l + r) / 2;
            if (Check(ind - m, ind + m)) {
                l = m;
            }
            else {
                r = m;
            }
        }
        cout << l * 2 + 1 << ' ';
    }
}
