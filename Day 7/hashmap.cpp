#include <bits/stdc++.h>
using namespace std;

template<class K, class V>
class HashMap {
private:
    class MapNode {
    public:
        K key;
        V value;
        MapNode* next;
        MapNode(K key, V value) : key(key), value(value), next(nullptr) {}
    };

    vector<MapNode*> buckets;
    int size;
    const float loadFactorThreshold = 0.75;

    int getBucketIndex(K key) {
        hash<K> hashFunc;
        int hashcode = hashFunc(key);
        return abs(hashcode) % buckets.size();
    }

    void rehash() {
        vector<MapNode*> oldBuckets = buckets;
        buckets.clear();
        buckets.resize(oldBuckets.size() * 2, nullptr);
        size = 0;
        for (auto head : oldBuckets) {
            MapNode* temp = head;
            while (temp != nullptr) {
                put(temp->key, temp->value);
                MapNode* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
    }

public:
    HashMap(int bucketSize = 10) {
        buckets.resize(bucketSize, nullptr);
        size = 0;
    }

    ~HashMap() {
        for (auto bucket : buckets) {
            MapNode* current = bucket;
            while (current) {
                MapNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    int getSize() {
        return size;
    }

    V get(K key) {
        int bucketIndex = getBucketIndex(key);
        MapNode* temp = buckets[bucketIndex];
        while (temp != nullptr) {
            if (temp->key == key) return temp->value;
            temp = temp->next;
        }
        return V();
    }

    void put(K key, V value) {
        int bucketIndex = getBucketIndex(key);
        MapNode* head = buckets[bucketIndex];
        while (head != nullptr) {
            if (head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }
        MapNode* newNode = new MapNode(key, value);
        newNode->next = buckets[bucketIndex];
        buckets[bucketIndex] = newNode;
        size++;
        float loadFactor = (1.0 * size) / buckets.size();
        if (loadFactor > loadFactorThreshold) {
            rehash();
        }
    }
};

int main() {
    HashMap<int, string> map;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int key;
        string value;
        cin >> key >> value;
        map.put(key, value);
    }
    int searchKey;
    cin >> searchKey;
    cout << map.get(searchKey) << endl;
    return 0;
}
