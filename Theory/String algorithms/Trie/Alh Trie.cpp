class Trie {
public:
    struct TrieNode {
        map<char, TrieNode*> children;
        TrieNode() : {}
    };

    Trie() {
        root = new TrieNode();
    }

    void add(const string& word) {
        private_add(word);
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
        }
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
