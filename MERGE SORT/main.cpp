#include<iostream>

using namespace std;

// Define a structure for a Node in a singly linked list
struct Node {
    int data;
    Node* next;
};

// Function to create a new node with given data
Node* new_Node(int data) {
    // Allocate memory for a new node
    Node* node = new Node();
    // Set the data for the new node
    node->data = data;
    // Set the next pointer of the new node to NULL
    node->next = NULL;
    return node;
}

// Function to merge two sorted linked lists
Node* sorted_Merge(Node* x, Node* y) {
    Node* result = NULL;

    // Base cases for recursion
    if (!x)
        return y;
    if (!y)
        return x;

    // Pick either node from x or y, and continue merging
    if (x->data <= y->data) {
        result = x;
        result->next = sorted_Merge(x->next, y);
    } else {
        result = y;
        result->next = sorted_Merge(x, y->next);
    }
    return result;
}

// Function to find the middle of a linked list
Node* getMiddle(Node* head) {
    if (!head)
        return head;

    Node *slow = head, *fast = head;
    // Use slow and fast pointers to find the middle node
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Function implementing the merge sort algorithm for linked list
Node* mergeSort(Node* head) {
    if (!head || !head->next)
        return head;

    // Split the linked list into two halves
    Node *middle = getMiddle(head);
    Node *nextOfMiddle = middle->next;
    middle->next = NULL;

    // Recursively sort the two halves
    Node *left = mergeSort(head);
    Node *right = mergeSort(nextOfMiddle);

    // Merge the sorted halves
    Node *sortedList = sorted_Merge(left, right);
    return sortedList;
}

// Function to display the elements of a linked list
void displayList(Node* head) {
    // Traverse the list and print each element
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Main function where the execution starts
int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    Node* list = NULL;
    Node* tail = NULL;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        int data;
        cin >> data;
        Node* newNode = new_Node(data);
        if (!list) {
            list = newNode;
            tail = list;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
    }

    cout << "Original list: ";
    displayList(list);

    // Perform merge sort on the list
    Node* result = mergeSort(list);
    cout << "\nAfter sorting the list: ";
    displayList(result);

    // Free allocated memory
    while (result) {
        Node* temp = result;
        result = result->next;
        delete temp;
    }

    return 0; // Indicates successful completion of the program
}
