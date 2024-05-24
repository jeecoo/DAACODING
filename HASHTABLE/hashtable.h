#include <iostream>
#include <string>

using namespace std;

class HashTable {
    string* table;
    int N;
    int count;

    // Polynomial hashing function
    int hash_code(const string& key) {
        const int p = 31; // A prime number
        const int a = 7;  // New constant 'a'
        int hash_value = 0;
        int power_of_p = 1;

        for (char c : key) {
            hash_value = (hash_value + (c - 'a' + 1) * power_of_p) % N;
            power_of_p = (power_of_p * a) % N;
        }

        return hash_value;
    }

    // MAD compression function
    int compress(int code) {
        int a = 59;
        int b = 17;
        int p = 509;
        return (((a * code) + b) % p) % N;
    }

    // Quadratic probing
    int probe(int index, int i) {
        return (index + i * i) % N;
    }

public:
    HashTable(int N) {
        table = new string[N];
        this->N = N;
        this->count = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    int insert(const string& key) {
        int index = compress(hash_code(key));
        int collisions = 0;
        int i = 1;

        while (!table[index].empty()) {
            if (table[index] == key) {
                return -1; // Key already exists
            }
            index = probe(index, i);
            collisions++;
            i++;
        }
        table[index] = key;
        count++;
        return collisions;
    }

    int search(const string& key) {
        int index = compress(hash_code(key));
        int cells = 0;
        int i = 1;

        while (!table[index].empty()) {
            if (table[index] == key) {
                return cells; // Found the key
            }
            index = probe(index, i);
            cells++;
            i++;
        }
        return -1; // Key not found
    }

    int remove(const string& key) {
        int index = compress(hash_code(key));
        int cells = 0;
        int i = 1;

        while (!table[index].empty()) {
            if (table[index] == key) {
                table[index] = ""; // Mark as removed
                count--;
                return cells; // Key removed
            }
            index = probe(index, i);
            cells++;
            i++;
        }
        return -1; // Key not found
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << i << "\t";
        }
        cout << "\n";
        for (int i = 0; i < N; i++) {
            if (!table[i].empty()) {
                cout << table[i] << "\t";
            } else {
                cout << "" << "\t";
            }
        }
        cout << "\n";
    }
};
