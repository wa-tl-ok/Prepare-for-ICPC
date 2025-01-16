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

class TRA {
public:
    struct TrieNode {
        map<char, TrieNode*> children;
        TrieNode* parent;

        bool term;

        int count;

        TrieNode() :
            parent(nullptr),
            term(false),
            count(0) {}

        int num = 0;
    };

    int NUM = 0;

    TRA() {
        root = new TrieNode();
        for (char c = 'a'; c <= 'b'; ++c) {
            alh.push_back(c);
        }
        A = (int)alh.size();
    }

    void add(const string& word) {
        TrieNode* current = root;

        root->num = 0;

        for (int i = 0; i < word.size(); i++) {
            char c = word[i];

            NUM += 1;

            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
                current->children[c]->parent = current;

                letter[{current, current->children[c]}] = c;
                letter[{current->children[c], current}] = c;
                sigma[{current, c}] = current->children[c];
            }

            current = current->children[c];

            current->num = NUM;
        }

        current->term = true;
    }

    void BUILD() {
        BUILD_TRA();
    }

private:
    TrieNode* root;

    int A;
    vector<char> alh;

    map<pair<TrieNode*, TrieNode*>, char> letter;

    map<TrieNode*, TrieNode*> suf_link;
    map<pair<TrieNode*, char>, TrieNode*> sigma;

    void BUILD_TRA() {
        queue<TrieNode*> Q; Q.push(root);

        while (Q.size() > 0) {
            TrieNode* current = Q.front(); Q.pop();

            if (current == root) {
                suf_link[current] = root;
            }
            else {
                char L = letter[{current, current->parent}];

                if (current->parent == root) {
                    suf_link[current] = root;
                }
                else {
                    suf_link[current] = sigma[{suf_link[current->parent], L}];
                }
            }
            for (char c : alh) {
                if (sigma[{current, c}] == nullptr) {
                    if (current == root) {
                        sigma[{current, c}] = root;
                    }
                    else {
                        sigma[{current, c}] = sigma[{suf_link[current], c}];
                    }
                }
                else {
                    
                }
            }

            for (auto c_v : current->children) {
                Q.push(c_v.second);
            }
        }
    }

public:
    /*
       Solving problem:
           Given a string T and a set of strings S [alh = {'a', 'b'}].
           For each string s from the set, determine:
           how many times it can be found as a substring in T?

           --- O(T.size() + TRA.size()) ---
    */

    TrieNode* now = nullptr;

    void go(char c) {
        if (now == nullptr) {
            now = root;
        }
        now = sigma[{now, c}];
        now->count += 1;
    }

    map<TrieNode*, vector<TrieNode*>> G;

    void solve() {
        for (auto u : suf_link) {
            if (u.second == root && u.first == root) {
                continue;
            }
            G[u.second].push_back(u.first);
        }
        dfs(root);
    }

    void dfs(TrieNode* u) {
        for (auto v : G[u]) {
            dfs(v);
            u->count += v->count;
        }
    }

    int find(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return 0;
            }
            current = current->children[c];
        }
        return current->count;
    }
};

void Solve() {
    /*
 --- Input ---
aabbababbaaa
3
aab
ab
bba

 --- Output ---
1 3 2

 --- Input ---
abbab
2
b
aba

 --- Output ---
3 0
    */

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string T; cin >> T;
    int n; cin >> n;

    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        v.push_back(s);
    }

    TRA tra;
    for (auto s : v) {
        tra.add(s);
    }

    tra.BUILD();

    for (int i = 0; i < T.size(); i++) {
        tra.go(T[i]);
    }

    tra.solve();

    for (auto a : v) {
        cout << tra.find(a) << ' ';
    }
}

#include <cassert>

string generateRandomString(int length) {
    string result;
    for (int i = 0; i < length; i++) {
        result += (rand() % 2 == 0 ? 'a' : 'b');
    }
    return result;
}

string get(string& t, int start, int len) {
    string ans = "";
    for (int i = start; i < start + len; i++) {
        ans += t[i];
    }
    return ans;
}

int C(string& t, string& s) {
    int ans = 0;
    for (int i = 0; i < t.size() - s.size(); i++) {
        if (get(t, i, s.size()) == s) {
            ++ans;
        }
    }
    return ans;
}

vector<int> naiveCount(string& T, const vector<string>& S) {
    string TT = T;
    for (int i = 0; i < 10; i++) {
        TT += "c";
    }
    vector<int> ans;
    for (auto s : S) {
        ans.push_back(C(TT, s));
    }
    return ans;
}

void TEST() {
    srand(time(nullptr));

    const int MAX_T_LENGTH = 1000;
    const int MAX_S_COUNT = 10;
    const int MAX_S_LENGTH = 10;

    for (int test = 1; test <= 100'000; test++) {
        int tLength = rand() % MAX_T_LENGTH + 1;
        string T = generateRandomString(tLength);

        int sCount = rand() % MAX_S_COUNT + 1;
        vector<string> S;
        for (int i = 0; i < sCount; i++) {
            int sLength = rand() % MAX_S_LENGTH + 1;
            S.push_back(generateRandomString(sLength));
        }

        TRA tra;
        for (const auto& s : S) {
            tra.add(s);
        }
        tra.BUILD();
        for (char c : T) {
            tra.go(c);
        }
        tra.solve();
        vector<int> traResult;
        for (const auto& s : S) {
            traResult.push_back(tra.find(s));
        }

        vector<int> naiveResult = naiveCount(T, S);

        if (traResult != naiveResult) {
            cout << "\nWA\n";

            cout << T << endl;
            cout << S.size() << endl;
            for (auto s : S) {
                cout << s << endl;
            }

            cout << "your answer ---> ";
            for (auto p : traResult) { cout << p << ' '; } cout << endl;
            cout << "test answer ---> ";
            for (auto p : naiveResult) { cout << p << ' '; } cout << endl;

            exit(0);
        }

        if (test % 10 == 0) {
            cout << "Test " << test << " passed!" << endl;
        }
    }

    cout << "All tests passed successfully!" << endl;
}

signed main() {
    //TEST();
    Solve();

    return 0;
}
