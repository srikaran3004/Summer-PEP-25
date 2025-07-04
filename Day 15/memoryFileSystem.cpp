#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string name;
    bool isFile;
    string content;
    vector<Node*> children;

    Node(string name, bool isFile = false) : name(name), isFile(isFile) {}
};

// Root directory
Node* root = new Node("/");

vector<string> split(string path) {
    vector<string> parts;
    string temp;
    for (char c : path) {
        if (c == '/') {
            if (!temp.empty()) parts.push_back(temp);
            temp = "";
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) parts.push_back(temp);
    return parts;
}

// Find node along a path, return nullptr if not found
Node* findNode(Node* current, vector<string>& parts, bool stopBeforeLast = false) {
    for (size_t i = 0; i < parts.size() - (stopBeforeLast ? 1 : 0); ++i) {
        bool found = false;
        for (auto child : current->children) {
            if (child->name == parts[i] && !child->isFile) {
                current = child;
                found = true;
                break;
            }
        }
        if (!found) return nullptr;
    }
    return current;
}

bool mkdir(string path) {
    vector<string> parts = split(path);
    if (parts.empty()) return false;

    Node* parent = findNode(root, parts, true);
    if (!parent) return false;

    string dirName = parts.back();
    // Check if it already exists
    for (auto child : parent->children) {
        if (child->name == dirName) return false;
    }

    parent->children.push_back(new Node(dirName));
    return true;
}

bool write_file(string path, string data) {
    vector<string> parts = split(path);
    if (parts.empty()) return false;

    Node* parent = findNode(root, parts, true);
    if (!parent) return false;

    string fileName = parts.back();
    // Check if file already exists
    for (auto child : parent->children) {
        if (child->name == fileName) {
            if (!child->isFile) return false;
            child->content = data;
            return true;
        }
    }

    Node* file = new Node(fileName, true);
    file->content = data;
    parent->children.push_back(file);
    return true;
}

string read_file(string path) {
    vector<string> parts = split(path);
    if (parts.empty()) return "Error: Invalid path";

    Node* current = root;
    for (string& part : parts) {
        bool found = false;
        for (auto child : current->children) {
            if (child->name == part) {
                current = child;
                found = true;
                break;
            }
        }
        if (!found) return "Error: Not found";
    }

    if (!current->isFile) return "Error: Not a file";

    return current->content;
}

int main() {
    cout << mkdir("/a") << endl;               // 1
    cout << mkdir("/a/b") << endl;             // 1
    cout << mkdir("/x/y") << endl;             // 0

    cout << write_file("/a/b/file.txt", "hello") << endl; // 1
    cout << write_file("/a/x/file.txt", "fail") << endl;  // 0

    cout << read_file("/a/b/file.txt") << endl; // hello
    cout << read_file("/a/x/file.txt") << endl; // Error: Not found

    return 0;
}
