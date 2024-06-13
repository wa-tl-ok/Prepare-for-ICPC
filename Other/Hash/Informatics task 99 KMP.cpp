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
vector<ll> Step(100005);
vector<ll> Pref_Hash_S;

ll Take_Hash(int l, int r) {
	if (l == 0) {
		return (((Pref_Hash_S[r] + mod) % mod) * Step[(int)S.size() - l]) % mod;
	}
	return (((Pref_Hash_S[r] - Pref_Hash_S[l - 1] + mod) % mod) * Step[(int)S.size() - l]) % mod;
}

int main() {
	cin >> S >> T;
	int PS = (int)S.size();
	S = S + T;

	Step[0] = 1;
	for (int i = 1; i < 100005; ++i) {
		Step[i] = (Step[i - 1] * 31) % mod;
	}

	Pref_Hash_S.resize((int)S.size());
	Pref_Hash_S[0] = S[0] - 'a' + 1;
	for (int i = 1; i < (int)S.size(); ++i) {
		Pref_Hash_S[i] = (Pref_Hash_S[i - 1] + ((S[i] - 'a' + 1) * Step[i]) % mod) % mod;
	}

	if (PS < T.size()) {
		cout << "";
	}
	else {
		int l, r, kl, kr;
		kl = PS;
		kr = (int)S.size() - 1;
		for (l = 0; l < (int)S.size(); ++l) {
			r = l + (int)T.size() - 1;
			if (r == PS) {
				break;
			}
			if (Take_Hash(l, r) == Take_Hash(kl, kr)) {
				cout << l << ' ';
			}
		}
	}
}
