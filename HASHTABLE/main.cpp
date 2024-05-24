#include <iostream>
#include "hashtable.h"
using namespace std;

int main() {
    int n;
    cout << "Enter the capacity of N: ";
    cin >> n;

    HashTable *table = new HashTable(n);

    char op;
    string key;

    do {
        cout << "Operation: ";
        cin >> op;
        switch(op) {
            case 'i':
                cin >> key;
                table->insert(key);
                break;
            case 's':
                cin >> key;
                cout << table->search(key);
                cout << "\n";
                break;
            case 'r':
                cin >> key;
                table->remove(key);
                break;
            case 'p':
                table->print();
                break;
            case 'x':
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid" << endl;
        }
    } while(op != 'x');

//    delete table;

    return 0;
}
