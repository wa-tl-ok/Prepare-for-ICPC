class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void Add(int data) {
        root = insertNode(root, data);
    }

    void Del(int data) {
        root = deleteNode(root, data);
    }

    bool Find(int data) const {
        if (findNode(root, data) == nullptr) {
            return false;
        }
        else {
            return true;
        }
    }

    void Print() const {
        printTree(root);
        cout << endl;
    }
private:
    struct Node {
        int data;

        Node* leftChild;
        Node* rightChild;

        int height;

        Node(int d) : 
            data(d), 
            leftChild(nullptr), rightChild(nullptr), 
            height(1) {}
    };

    Node* root;

    int height(Node* N) const {
        if (N == nullptr) {
            return 0;
        }
        else {
            return N->height;
        }
    }

    int max(int a, int b) const {
        if (a > b) {
            return a;
        }
        else {
            return b;
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->leftChild;
        Node* z = x->rightChild;

        x->rightChild = y;
        y->leftChild = z;

        y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
        x->height = max(height(x->leftChild), height(x->rightChild)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->rightChild;
        Node* z = y->leftChild;

        y->leftChild = x;
        x->rightChild = z;

        x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
        y->height = max(height(y->leftChild), height(y->rightChild)) + 1;

        return y;
    }

    int getBalance(Node* N) const {
        if (N == nullptr) {
            return 0;
        }
        else {
            return height(N->leftChild) - height(N->rightChild);
        }
    }

    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data)
            node->leftChild = insertNode(node->leftChild, data);
        else if (data > node->data)
            node->rightChild = insertNode(node->rightChild, data);
        else
            return node;

        node->height = 1 + max(height(node->leftChild), height(node->rightChild));

        int balance = getBalance(node);

        if (balance > 1 && data < node->leftChild->data)
            return rightRotate(node);

        if (balance < -1 && data > node->rightChild->data)
            return leftRotate(node);

        if (balance > 1 && data > node->leftChild->data) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->rightChild->data) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) const {
        Node* current = node;

        while (current && current->leftChild != nullptr)
            current = current->leftChild;

        return current;
    }

    Node* deleteNode(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }

        if (data < root->data)
            root->leftChild = deleteNode(root->leftChild, data);
        else if (data > root->data)
            root->rightChild = deleteNode(root->rightChild, data);
        else {
            if (root->leftChild == nullptr || root->rightChild == nullptr) {
                Node* temp = root->leftChild ? root->leftChild : root->rightChild;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }

                delete temp;
            }
            else {
                Node* temp = minValueNode(root->rightChild);

                root->data = temp->data;
                root->rightChild = deleteNode(root->rightChild, temp->data);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + max(height(root->leftChild), height(root->rightChild));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->leftChild) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->leftChild) < 0) {
            root->leftChild = leftRotate(root->leftChild);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->rightChild) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->rightChild) > 0) {
            root->rightChild = rightRotate(root->rightChild);
            return leftRotate(root);
        }

        return root;
    }

    Node* findNode(Node* root, int data) const {
        if (root == nullptr || root->data == data)
            return root;

        if (data < root->data)
            return findNode(root->leftChild, data);

        return findNode(root->rightChild, data);
    }

    void printTree(Node* root) const {
        if (root != nullptr) {
            printTree(root->leftChild);
            cout << root->data << " ";
            printTree(root->rightChild);
        }
    }
};
