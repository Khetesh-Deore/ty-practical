#include <iostream>
#include <string>
using namespace std;

// Node structure for AVL Tree
class Node {
public:
    string key;
    string value;
    Node* left;
    Node* right;
    int height;

    Node(string k, string v) {
        key = k;
        value = v;
        left = right = NULL;
        height = 1;
    }
};

// AVL Dictionary class
class AVLDictionary {
    Node* root;

    // Get height of a node
    int height(Node* n) {
        return n ? n->height : 0;
    }

    // Get balance factor
    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    // Right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    // Left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // Insert (key, value) into AVL
    Node* insert(Node* node, string key, string value) {
        if (node == NULL)
            return new Node(key, value);

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else {
            cout << "Duplicate key not allowed!\n";
            return node;
        }

        // Update height
        node->height = 1 + max(height(node->left), height(node->right));

        // Balance factor
        int balance = getBalance(node);

        // Balancing cases
        if (balance > 1 && key < node->left->key)
            return rightRotate(node); // Left Left
        if (balance < -1 && key > node->right->key)
            return leftRotate(node); // Right Right
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node); // Left Right
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node); // Right Left
        }
        return node;
    }

    // Find minimum node
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    // Delete a key
    Node* deleteNode(Node* root, string key) {
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp)
                    root = NULL;
                else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        // Balancing after deletion
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Search key
    Node* search(Node* node, string key, int& comparisons) {
        if (!node) return NULL;
        comparisons++;
        if (node->key == key)
            return node;
        else if (key < node->key)
            return search(node->left, key, comparisons);
        else
            return search(node->right, key, comparisons);
    }

    // Ascending order traversal
    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " : " << root->value << endl;
            inorder(root->right);
        }
    }

    // Descending order traversal
    void reverseInorder(Node* root) {
        if (root) {
            reverseInorder(root->right);
            cout << root->key << " : " << root->value << endl;
            reverseInorder(root->left);
        }
    }

public:
    AVLDictionary() { root = NULL; }

    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    void remove(string key) {
        root = deleteNode(root, key);
    }

    void find(string key) {
        int comparisons = 0;
        Node* res = search(root, key, comparisons);
        if (res)
            cout << "Found: " << res->key << " → " << res->value << " (Comparisons: " << comparisons << ")\n";
        else
            cout << "Key not found! (Comparisons: " << comparisons << ")\n";
    }

    void displayAscending() {
        cout << "\nDictionary (Ascending Order):\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "\nDictionary (Descending Order):\n";
        reverseInorder(root);
    }

    void maxComparisons() {
        if (!root) cout << "Tree is empty!\n";
        else cout << "Maximum comparisons required ≈ O(log n)\n";
    }
};

// ---------------- Main Program ----------------
int main() {
    AVLDictionary dict;
    int choice;
    string key, value;

    do {
        cout << "\n--- AVL Dictionary Menu ---\n";
        cout << "1. Insert (Key, Value)\n";
        cout << "2. Find a Key\n";
        cout << "3. Delete a Key\n";
        cout << "4. Display Ascending Order\n";
        cout << "5. Display Descending Order\n";
        cout << "6. Show Maximum Comparisons (Complexity)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Key: ";
            cin >> key;
            cout << "Enter Value: ";
            cin >> value;
            dict.insert(key, value);
            break;
        case 2:
            cout << "Enter Key to Search: ";
            cin >> key;
            dict.find(key);
            break;
        case 3:
            cout << "Enter Key to Delete: ";
            cin >> key;
            dict.remove(key);
            break;
        case 4:
            dict.displayAscending();
            break;
        case 5:
            dict.displayDescending();
            break;
        case 6:
            dict.maxComparisons();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
