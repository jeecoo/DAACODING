#include <iostream>
#include "reblack.h"

using namespace std;

int main(int argc, char** argv){
    RedBlack* tree = new RedBlack();
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
            case 'r':
                cin >> num;
//                tree->remove(num);
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
