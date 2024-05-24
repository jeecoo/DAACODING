#include <cstdlib>
#include <iostream>

#include "node.h"

using namespace std;

class SplayTree{
    node* root;
    int size;

    node *create_node(int element, bool is_red = true, node *parent = NULL) {
        node *newNode = new node();
        newNode->right = NULL;
        newNode->left =  NULL;
        newNode->element = element;
        newNode->is_red = is_red;
        newNode->parent = parent;
        size++;
        return newNode;
    }

public:
    SplayTree(){
        root = NULL;
        size = 0;
    }

    bool insert(int num) {
        insert(root, num, NULL, false);
        return true;
    }

    bool insert(node *curr, int num, node *par, bool is_left){

        if (root == NULL) {
            root = create_node(num, false, NULL);
            return true;
        }

        if (curr == NULL) {
            node *n = create_node(num, true, par);

            if (is_left)
                par->left = n;
            else
                par->right = n;

            restructure(n);
            return true;
        }

        if (curr->element > num) {
            insert(curr->left, num, curr, true);
        }else {
            insert(curr->right, num, curr, false);
        }

        restructure(curr);
        return true;
    }

    bool remove(int num) {
        remove(root, num, NULL, false);
        return true;
    }

    bool remove(node *curr, int num, node *par, bool is_left){
        if (root == NULL) {
            root = create_node(num, false, NULL);
            return true;
        }

        if (curr == NULL) {
            node *n = create_node(num, true, par);

            if (is_left)
                par->left = n;
            else
                par->right = n;

            restructure(n);
            return true;
        }

        if (curr->element > num) {
            insert(curr->left, num, curr, true);
        }else {
            insert(curr->right, num, curr, false);
        }

        restructure(curr);
        return true;
    }

    //RECOLOR
    void recolor(node *curr) {
        curr->is_red = false;
        curr->left->is_red = true;
        curr->right->is_red = true;
    }


    //RESTRUCTURING METHOD
    bool restructure(node *child) {
        node *par = child->parent;

        if (!par || !par->is_red || !child->is_red)
            return true;

        node *gp = par->parent;
        node *sib = gp->left == par ? gp->right : gp->left;

        //CHECK IF UNCLE IS BLACK/NONE
        if (!sib || !sib->is_red) {
//			      "CASE 1: TRINODE RESTRUCTURING"
            bool ptop_right = par->left == child;
            bool gtop_right = gp->left == par;

            if (gtop_right && ptop_right) {
                zigright(par);
                recolor(par);
//			        cout << "ZIGRIGHT" << endl;
            } else if (gtop_right && !ptop_right) {
                zigleft(child);
                zigright(child);
                recolor(child);
//			        cout << "ZIGZAGRIGHT" << endl;
            } else if (!gtop_right && !ptop_right) {
                zigleft(par);
                recolor(par);
//			        cout << "ZIGLEFT" << endl;
            } else {
                zigright(child);
                zigleft(child);
                recolor(child);
//			        cout << "ZIGZAGLEFT" << endl;
            }

            //UNCLE IS RED
        } else {
//			      cout << "CASE 2: PERFORM RECOLOR" << endl;

            par->is_red = false;
            sib->is_red = false;

            if (gp != root)
                gp->is_red = true;

            return true;
        }

        return true;
    }

    void zigleft(node *curr) {
        node *x = curr;
        node *y = x->parent;
        node *z = y->parent;

        if (z == NULL)
            root = x;
        else if (y == z->left)
            z->left = x;
        else
            z->right = x;

        x->parent = z;
        y->parent = x;

        if (x->left)
            x->left->parent = y;
        y->right = x->left;

        x->left = y;
    }

    void zigright(node *curr) {
        node *x = curr;
        node *y = x->parent;
        node *z = y->parent;

        if (z == NULL)
            root = x;
        else if (y == z->left)
            z->left = x;
        else
            z->right = x;

        y->parent = x;
        x->parent = z;

        if (x->right)
            x->right->parent = y;
        y->left = x->right;

        x->right = y;
    }

    void print(){
        cout << "Size: " << size << endl;
        print(" ", 'Q', root);
    }

    void print(string pre, char loc, node* n){
        if(!n)
            return;
        cout << pre <<"|--" << loc <<": " << n->element;
        if(n->is_red)
            cout << "(R)" << endl;
        else
            cout << "(B)" << endl;

        print(pre+"    ", 'L', n->left);
        print(pre+"    ", 'R', n->right);
    }
};
