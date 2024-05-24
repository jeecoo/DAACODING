#include <iostream>
using namespace std;

// Utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Partition function
int partition(int arr[], int start, int end) {
    int pivot = arr[start]; // Pivot
    int green = start + 1; // Index of smaller element
    int purple = end; // Index of larger element

    while (true) {
        // Move i forward until it finds an element greater than pivot
        while (green <= purple && arr[green] <= pivot) {
            green++;
        }

        // Move j backward until it finds an element smaller than pivot
        while (green <= purple && arr[purple] >= pivot) {
            purple--;
        }


        if (green < purple) {
            cout << "GWAPO ";
            swap(&arr[green], &arr[purple]);
            print(arr, end + 1);
        } else {
            break;
        }
    }

    if (start < purple) {
        cout << "GWAPA ";
        swap(arr[start], arr[purple]);
        print(arr, end + 1); // Print array after swap
    }

    return purple; // Return the index of the pivot after repositioning
}

// Recursive function to perform QuickSort
void quickSort(int arr[], int start, int end) {
    if (start < end) {
        int pi = partition(arr, start, end);
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);
    }
}

// Main function
int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int* array = new int[n];

    for (int i = 0; i < n; ++i) {
        cout << "Enter element " << i + 1<< ": ";
        cin >> array[i];
    }

    cout << "Original Array: ";
    print(array, n);

    quickSort(array, 0, n - 1);

    cout << "Sorted Array: ";
    print(array, n);

    return 0;
}
