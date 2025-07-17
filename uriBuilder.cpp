#include <bits/stdc++.h>
using namespace std;

class uriBuilder {
private:
    string schema;
    string host;
    int port;
    string path;

public:
    void setSchema(string s) {
        schema = s;
    }

    void setHost(string h) {
        host = h;
    }

    void setPort(int p) {
        port = p;
    }

    void setPath(string p) {
        path = p;
    }

    string build() {
        string uri = schema + "://" + host;
        if (port != 0) {
            uri += ":" + to_string(port);
        }
        if (!path.empty()) {
            if (path[0] != '/') uri += "/";
            uri += path;
        }
        return uri;
    }
};

int main() {
    uriBuilder builder;

    builder.setSchema("https");
    builder.setHost("example.com");
    builder.setPort(443);
    builder.setPath("page");

    string uri = builder.build();
    cout << "Built URI: " << uri << endl;

    return 0;
}
