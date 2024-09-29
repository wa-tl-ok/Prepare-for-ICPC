class Trie {
public:
    struct TrieNode {
        int count;
        map<char, TrieNode*> children;

        TrieNode() : count(0) {}
    };

    Trie() {
        root = new TrieNode();
    }

    void add(const string& word) {
        private_add(word);
    }

    int query(const string& prefix) {
        return private_query(prefix);
    }

    bool find(const string& word) {
        return private_find(word);
    }
private:
    TrieNode* root;

    void private_add(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }

            current = current->children[c];

            current->count++;
        }
    }

    int private_query(const string& prefix) {
        TrieNode* current = root;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return 0;
            }

            current = current->children[c];
        }

        return current->count;
    }

    bool private_find(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }

            current = current->children[c];
        }

        return true;
    }
};
