#include <iostream>

using namespace std;

class TokenBucketRateLimiter {
private:
    int capacity;
    double tokens;
    double refillRatePerSec;
    long lastRefillTime;  // Simulated time in seconds

public:
    TokenBucketRateLimiter(int cap, double rate)
        : capacity(cap), tokens(cap), refillRatePerSec(rate), lastRefillTime(0) {}

    bool allowRequest(long currentTime) {
        long elapsed = currentTime - lastRefillTime;

        // Refill tokens
        tokens += elapsed * refillRatePerSec;
        if (tokens > capacity) tokens = capacity;

        lastRefillTime = currentTime;

        // Allow if there's at least 1 token
        if (tokens >= 1.0) {
            tokens -= 1.0;
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    TokenBucketRateLimiter limiter(5, 1.0); // 5 tokens max, 1 token/sec refill

    long simulatedTime = 0; // Start at "0 seconds"

    // Simulate 10 requests, 0.5s apart (i.e., every half second)
    for (int i = 1; i <= 10; ++i) {
        bool allowed = limiter.allowRequest(simulatedTime);
        cout << "Request " << i << " at time " << simulatedTime << "s: "
             << (allowed ? "Allowed" : "Blocked") << endl;

        // Advance simulated time by 0.5 seconds
        simulatedTime += 0.5;
    }

    return 0;
}
