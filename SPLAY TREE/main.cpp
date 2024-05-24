#include <iostream>
#include "splay.h"

using namespace std;

int main(int argc, char** argv){
    SplayTree* tree = new SplayTree();
    char op;
    int num;

    do{
        cout << "Op: ";
        cin >> op;
        switch(op){
            case 'i':
                cin >> num;
                tree->insert(num);
                break;
            case 's':
                cin >> num;
                tree->search(num);
            case 'r':
                cin >> num;
                tree->remove(num);
            case 'p':
                tree->print();
                break;
            case 'x':
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid" << endl;
        }
    }while(op != 'x');
    return 0;
}
