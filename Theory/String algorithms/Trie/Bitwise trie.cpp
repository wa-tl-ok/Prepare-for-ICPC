class Bitwise_trie {
public:
    struct TrieNode {
        int count;
        TrieNode* children[2];
        TrieNode* parent;

        TrieNode() : count(0), parent(nullptr) {
            children[0] = nullptr;
            children[1] = nullptr;
        }
    };

    Bitwise_trie() {
        root = new TrieNode();
    }

    void add(int num) {
        private_add(num);
    }

    void remove(int num) {
        private_remove(num);
    }

private:
    TrieNode* root;

    void private_add(int num) {
        TrieNode* current = root;
        current->count++;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;

            if (current->children[bit] == nullptr) {
                current->children[bit] = new TrieNode();
                current->children[bit]->parent = current;
            }

            current = current->children[bit];
            current->count++;
        }
    }

    void private_remove(int num) {
        TrieNode* current = root;
        current->count--;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;
            TrieNode* child = current->children[bit];
            child->count--;

            if (child->count == 0) {
                delete child;
                current->children[bit] = nullptr;
                return;
            }

            current = child;
        }
    }
};
