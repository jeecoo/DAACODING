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
}

void quickSort(int arr[], int start, int end) {
    if (start < end) {
        int pivot = arr[start];
        int green = start + 1;
        int purple = end;

        while (true) {
            while (green <= purple && arr[green] <= pivot)
                green++;
            while (purple >= green && arr[purple] >= pivot)
                purple--;
            if (purple < green)
                break;
            else {
                // Swap elements at green and purple
                int temp = arr[green];
                arr[green] = arr[purple];
                arr[purple] = temp;
                // Print array after each swap
//                for (int i = 0; i <= end; i++)
//                    cout << arr[i] << " ";
                print(arr, end+1);
                cout << endl;
            }
        }
        // Swap pivot with element at purple
        int temp = arr[start];
        arr[start] = arr[purple];
        arr[purple] = temp;
        // Print array after final swap
        for (int i = 0; i <= end; i++)
            cout << arr[i] << " ";
        cout << endl;

        // Recursively sort elements before and after partition
        quickSort(arr, start, purple - 1);
        quickSort(arr, purple + 1, end);
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
