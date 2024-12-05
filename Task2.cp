#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding random number generator

using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized partition
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

// Randomized Select function
int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low];
    }

    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1; // Position of the pivot element in the current subarray

    if (i == k) {
        return arr[pivotIndex];
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

int main() {
    srand(time(0)); // Seed random number generator

    int n, i;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int j = 0; j < n; j++) {
        cin >> arr[j];
    }

    cout << "Enter the value of i (1-based index): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid value of i. It should be between 1 and " << n << "." << endl;
        return 1;
    }

    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "-th smallest element is: " << result << endl;

    return 0;
}
