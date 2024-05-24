#include <string>

using namespace std;

class HashTable {
private:
    string* table;
    int N;
    int count;
    string DELETED;


    unsigned long long polynomialHash(const string& key) const {
        unsigned long long hash = 0;
        unsigned long long a = 7;
        for (char ch : key) {
            hash = hash * a + (ch - 'a' + 1);
        }
        return hash;
    }

    // MAD compression function with a = 11, b = 251, c = 319
    int compress(unsigned long long hash) const {
        unsigned long long a = 11;
        unsigned long long b = 251;
        unsigned long long c = 319;
        return (a * hash + b) % c;
    }

public:
    HashTable(int capacity) : N(capacity), count(0), DELETED("<DELETED>") {
        table = new string[N];
        for (int i = 0; i < N; ++i) {
            table[i] = "";
        }
    }

    ~HashTable() {
        delete[] table;
    }

    // Insert using quadratic probing
    void insert(const string& key) {
        unsigned long long hash = polynomialHash(key);
        int index = compress(hash);
        int i = 0;
        while (!table[(index + i * i) % N].empty() && table[(index + i * i) % N] != DELETED) {
            i++;
            if (i == N) {
                return;
            }
        }
        table[(index + i * i) % N] = key;
        count++;
    }

    // search using quadratic probing
    int search(const string& key) const {
        unsigned long long hash = polynomialHash(key);
        int index = compress(hash);
        int i = 0;
        while (!table[(index + i * i) % N].empty()) {
            if (table[(index + i * i) % N] == key) {
                return (index + i * i) % N; // Return the index where the key is found
            }

            i++;
            if (i == N) {
                break;
            }
        }
        return -1; // Key not found
    }

    // Remove using quadratic probing
    void remove(const string& key) {
        unsigned long long hash = polynomialHash(key);
        int index = compress(hash);
        int i = 0;
        while (!table[(index + i * i) % N].empty()) {
            if (table[(index + i * i) % N] == key) {
                table[(index + i * i) % N] = DELETED;
                count--;
                return;
            }
            i++;
            if (i == N) {
                break;
            }
        }
    }

    void print() const {
        for (int i = 0; i < N; ++i) {
            if (!table[i].empty() && table[i] != DELETED) {
                cout << "[" << i << "]: " << table[i] << endl;
            }
        }
    }

//    // Get the number of elements in the hash table
//    int size() const {
//        return count;
//    }
//
//    // Get the capacity of the hash table
//    int capacity() const {
//        return N;
//    }
};
