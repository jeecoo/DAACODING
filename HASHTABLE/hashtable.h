#include <string> // Include the string library

using namespace std;

class HashTable {
    string* table; // Changed to string pointer
    int N;
    int count;

    // Use the ASCII code of the character
    int hash_code(const string& key) {
        const int p = 31; // A prime number
        int hash_value = 0;
        int power_of_p = 1;

        for (char c : key) {
            hash_value = (hash_value + (c - 'a' + 1) * power_of_p) % N;
            power_of_p = (power_of_p * p) % N;
        }

        return hash_value;
    }

    // This hash table uses a MAD compression function
    // where a = 59, b = 17, p = 509

    int compress(int code) {
        int a = 59;
        int b = 17;
        int p = 509;
        return (((a * code) + b) % p) % N;
    }

    // Using the knowledge that a hash function is composed of two portions
    int hashfn(const string& key) {
        return compress(hash_code(key));
    }

public:
    HashTable(int N) {
        table = new string[N]; // Allocate memory for an array of strings
        this->N = N;
        this->count = 0;
    }

    ~HashTable() {
        delete[] table; // Deallocate memory
    }

    int insert(const string& key) { // Modified to accept a string key
        int index = hashfn(key);
        int collisions = 0;
        int i = 1; // Quadratic probing sequence counter

        while (!table[index].empty()) {
            if (table[index] == key) {
                return -1; // Key already exists
            }
            // Quadratic probing: increment index by i^2
            index = (index + i * i) % N;
            collisions++;
            i++; // Increment sequence counter
        }
        table[index] = key;
        count++;
        return collisions;
    }

    int search(const string& key) { // Modified to accept a string key
        int index = hashfn(key);
        int cells = 0;
        int i = 1; // Quadratic probing sequence counter

        while (!table[index].empty()) {
            if (table[index] == key) {
                return cells; // Found the key
            }
            // Quadratic probing: increment index by i^2
            index = (index + i * i) % N;
            cells++;
            i++; // Increment sequence counter
        }
        return -1; // Key not found
    }

    int remove(const string& key) { // Modified to accept a string key
        int index = hashfn(key);
        int cells = 0;
        int i = 1; // Quadratic probing sequence counter

        while (!table[index].empty()) {
            if (table[index] == key) {
                table[index] = ""; // Mark as removed
                count--;
                return cells; // Key removed
            }
            // Quadratic probing: increment index by i^2
            index = (index + i * i) % N;
            cells++;
            i++; // Increment sequence counter
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
