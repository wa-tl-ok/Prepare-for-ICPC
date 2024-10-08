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

class Trie {
public:
    struct TrieNode {
        int count;
        int depth;

        map<char, TrieNode*> children;
        TrieNode* parent;

        TrieNode() : count(0), depth(0) {}
    };

    map<int, TrieNode*> M;

    Trie() {
        root = new TrieNode();
    }

    void add(const string& word, int id) {
        private_add(word, id);
    }

    int query(const string& prefix, int id) {
        return private_query(prefix, id);
    }
private:
    TrieNode* root;

    void private_add(const string& word, int id) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();

                current->children[c]->parent = current;
                current->children[c]->depth = current->depth + 1;
            }

            current = current->children[c];
            current->count++;
        }

        M[id] = current;
    }

    int private_query(const string& prefix, int id) {
        TrieNode* current = M[id];

        while (current != root) {
            if (current->count > 1) {
                return current->depth;
            }
            current = current->parent;
        }

        return 0;
    }
};

void Solve() {
    int n; cin >> n;
    vector<string> S(n);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        S[i] = s;
    }
    Trie T;
    for (int i = 0; i < n; i++) {
        T.add(S[i], i);
    }
    for (int i = 0; i < n; i++) {
        cout << T.query(S[i], i) << '\n';
    }
}

int main() {
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
