#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class FixedWindowRateLimiter {
private:
    int maxRequests;
    int windowSizeSeconds;

    // Store: userKey -> (windowStartTime, requestCount)
    unordered_map<string, pair<int, int>> requestCounts;

public:
    FixedWindowRateLimiter(int maxReq, int windowSec)
        : maxRequests(maxReq), windowSizeSeconds(windowSec) {}

    bool allowRequest(const string& userKey, int currentTime) {
        int windowStart = currentTime - (currentTime % windowSizeSeconds);

        auto& entry = requestCounts[userKey];

        if (entry.first != windowStart) {
            // New window: reset count
            entry.first = windowStart;
            entry.second = 1;
        } else {
            // Same window: increment count
            entry.second++;
        }

        return entry.second <= maxRequests;
    }
};

int main() {
    FixedWindowRateLimiter limiter(5, 10); // Allow max 5 requests per 10 seconds

    int simulatedTime = 0; // Start at 0 seconds

    for (int i = 1; i <= 10; ++i) {
        bool allowed = limiter.allowRequest("user123", simulatedTime);
        cout << "Request " << i << " at time " << simulatedTime << "s: "
             << (allowed ? "Allowed" : "Blocked") << endl;

        simulatedTime += 1; // Simulate 1 second between each request
    }

    return 0;
}
