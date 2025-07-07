#include <iostream>
#include <queue>

class LeakyBucket {
public:
    LeakyBucket(int capacity, int leak_rate_per_second)
        : capacity(capacity), leak_rate(leak_rate_per_second), last_time(0) {}

    bool allow_request(int current_time) {
        int time_passed = current_time - last_time;
        int leaked = time_passed * leak_rate;

        while (leaked > 0 && !bucket.empty()) {
            bucket.pop();
            leaked--;
        }

        if (time_passed > 0) {
            last_time = current_time;
        }

        if (bucket.size() < capacity) {
            bucket.push(current_time);
            return true;
        }

        return false;
    }

private:
    int capacity;
    int leak_rate;
    int last_time;
    std::queue<int> bucket;
};

int main() {
    LeakyBucket limiter(5, 1);

    for (int i = 0; i < 10; ++i) {
        std::cout << "Time 0, Request " << i << ": "
                  << (limiter.allow_request(0) ? "Allowed" : "Denied") << std::endl;
    }

    std::cout << "Time 1, Request: "
              << (limiter.allow_request(1) ? "Allowed" : "Denied") << std::endl;

    std::cout << "Time 4, Request: "
              << (limiter.allow_request(4) ? "Allowed" : "Denied") << std::endl;

    return 0;
}
