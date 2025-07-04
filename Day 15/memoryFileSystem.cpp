#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

unordered_map<string, bool> isFile;
unordered_map<string, string> fileContent;

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

string joinPath(vector<string>& parts, int endIndex) {
    string path = "";
    for (int i = 0; i <= endIndex; ++i) {
        path += "/" + parts[i];
    }
    return path;
}

bool mkdir(string path) {
    vector<string> parts = split(path);
    if (parts.empty()) return false;

    string curr = "";
    for (int i = 0; i < parts.size(); ++i) {
        curr = joinPath(parts, i);
        if (i < parts.size() - 1 && isFile.find(curr) == isFile.end()) {
            return false;
        }
    }
    isFile[path] = false;
    return true;
}

bool write_file(string path, string content) {
    vector<string> parts = split(path);
    if (parts.empty()) return false;

    string curr = "";
    for (int i = 0; i < parts.size() - 1; ++i) {
        curr = joinPath(parts, i);
        if (isFile.find(curr) == isFile.end() || isFile[curr]) {
            return false;
        }
    }

    isFile[path] = true;
    fileContent[path] = content;
    return true;
}

string read_file(string path) {
    if (isFile.find(path) == isFile.end() || !isFile[path]) {
        return "Error: File not found";
    }
    return fileContent[path];
}

int main() {
    cout << mkdir("/a") << endl;
    cout << mkdir("/a/b") << endl;
    cout << mkdir("/x/y") << endl;

    cout << write_file("/a/b/file.txt", "hi") << endl;
    cout << write_file("/a/x/file.txt", "fail") << endl;

    cout << read_file("/a/b/file.txt") << endl;
    cout << read_file("/a/x/file.txt") << endl;

    return 0;
}
