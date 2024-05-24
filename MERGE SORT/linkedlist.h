#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        Node* current = head;
        Node* next;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void add(int data) {
        Node* temp = new Node;
        temp->data = data;
        temp->next = nullptr;

        if (head == nullptr) {
            head = temp;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = temp;
        }
    }

    void display() {
        Node* temp = head;
        if (head == nullptr) {
            std::cout << "List is empty";
            return;
        }
        while (temp != nullptr) {
            std::cout << temp->data << "-->";
            temp = temp->next;
        }
    }

    void mergeSort() {
        // Implement merge sort here
    }

    void merge(Node* h2, int s1, int s2) {
        // Implement merge function here
    }

private:
    Node* head;
};

#endif
